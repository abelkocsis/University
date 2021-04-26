#include <string>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <string.h>

#include "network_interface.h"
#include <boost/asio.hpp>
#include "chat_message.hpp"

#pragma once
// DO NOT INCLUDE BOOST HERE!
// Use network.cpp for that.
// Use mock_network.cpp for a fake implementation for tests.
// feel free to change the interface, but do it in BOTH cpps.

using boost::asio::ip::tcp;

class chat_participant
{
public:
	virtual ~chat_participant() {}
	virtual void deliver(const chat_message& msg) = 0;
};

//----------------------------------------------------------------------

class chat_room
{
public:
	void join(std::shared_ptr<chat_participant> participant)
	{
		participants_.insert(participant);
		std::cout << "joined" << std::endl;
		for (auto msg : recent_msgs_)
			participant->deliver(msg);
	}

	void leave(std::shared_ptr<chat_participant> participant)
	{
		participants_.erase(participant);
	}

	void deliver(const chat_message& msg)
	{
		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() > MAX_RECENT_MSGS)
			recent_msgs_.pop_front();

		for (auto participant : participants_)
			participant->deliver(msg);
	}

private:
	static const int MAX_RECENT_MSGS = 100;

	std::set<std::shared_ptr<chat_participant>> participants_;
	std::deque<chat_message> recent_msgs_;
};

//----------------------------------------------------------------------

class chat_session
	: public chat_participant,
	public std::enable_shared_from_this<chat_session>
{
public:
	chat_session(tcp::socket socket, chat_room& room)
		: socket_(std::move(socket)),
		room_(room)
	{
	}

	void start()
	{
		room_.join(shared_from_this());
		do_read_header();
	}

	void deliver(const chat_message& msg)
	{
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress)
		{
			do_write();
		}
	}

private:
	void do_read_header()
	{
		auto self(shared_from_this());
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::HEADER_LENGTH),
			[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec && read_msg_.decode_header())
			{
				do_read_body();
			}
			else
			{
				room_.leave(shared_from_this());
			}
		});
	}

	void do_read_body()
	{
		auto self(shared_from_this());
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				room_.deliver(read_msg_);
				do_read_header();
			}
			else
			{
				room_.leave(shared_from_this());
			}
		});
	}

	void do_write()
	{
		auto self(shared_from_this());
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				write_msgs_.pop_front();
				if (!write_msgs_.empty())
				{
					do_write();
				}
			}
			else
			{
				room_.leave(shared_from_this());
			}
		});
	}

	tcp::socket socket_;
	chat_room& room_;
	chat_message read_msg_;
	std::deque<chat_message> write_msgs_;
};

//----------------------------------------------------------------------

class chat_server
{
public:
	chat_server(boost::asio::io_service& io_service,
		const tcp::endpoint& endpoint)
		: acceptor_(io_service, endpoint),
		socket_(io_service)
	{
		do_accept();
	}

private:
	void do_accept()
	{
		acceptor_.async_accept(socket_,
			[this](boost::system::error_code ec)
		{
			if (!ec)
			{
				std::make_shared<chat_session>(std::move(socket_), room_)->start();
			}

			do_accept();
		});
	}

	tcp::acceptor acceptor_;
	tcp::socket socket_;
	chat_room room_;
};

//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

class chat_client
{
public:
	chat_client(boost::asio::io_service& io_service,
		tcp::resolver::iterator endpoint_iterator)
		: io_service_(io_service),
		socket_(io_service), lastMessageNum(0)
	{
		do_connect(endpoint_iterator);
	}

	void write(const chat_message& msg)
	{
		io_service_.post(
			[this, msg]()
		{
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(msg);
			if (!write_in_progress)
			{
				do_write();
			}
		});
	}

	int get_lastMessageNum() { return lastMessageNum; }
	std::string& get_lastMessage() { return lastMessage; }

	void close()
	{
		io_service_.post([this]() { socket_.close(); });
	}

private:
	void do_connect(tcp::resolver::iterator endpoint_iterator)
	{
		boost::asio::async_connect(socket_, endpoint_iterator,
			[this](boost::system::error_code ec, tcp::resolver::iterator)
		{
			if (!ec)
			{
				do_read_header();
			}
		});
	}

	void do_read_header()
	{
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::HEADER_LENGTH),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec && read_msg_.decode_header())
			{
				do_read_body();
			}
			else
			{
				socket_.close();
			}
		});
	}

	void do_read_body()
	{
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{

				lastMessage.clear();
				for (size_t i = 0; i < read_msg_.body_length(); i++)
				{
					lastMessage.push_back(read_msg_.body()[i]);
				}


				lastMessageNum++;

				do_read_header();
			}
			else
			{
				socket_.close();
			}
		});
	}

	void do_write()
	{
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				write_msgs_.pop_front();
				if (!write_msgs_.empty())
				{
					do_write();
				}
			}
			else
			{
				socket_.close();
			}
		});
	}

private:
	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	chat_message read_msg_;
	std::deque<chat_message> write_msgs_;

	std::string lastMessage;
	int lastMessageNum;
};

//----------------------------------------------------------------------


class network : public parent_network
{
public:
	network();

	bool is_server;

	void init(bool is_server, const char * s_address, const char * s_port);

	void connect(const char * host, const char * port);

	void disconnect();

	void send_msg(std::string s);

	bool newMessage();

	std::string& receive_msg();

	~network();

private:
	bool server;
	bool initialized;
	
	int lastAsked;

	boost::asio::io_service io_service;
	boost::asio::io_service io_service_server;
	std::list<chat_server> servers;
	chat_client* client;
	std::thread* thread;
	std::thread* server_thread;
};


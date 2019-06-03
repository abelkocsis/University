// Copyright goes to Christopher M. Kohlhoff
// for the original version of this sample program.

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <string.h>

#include <boost/asio.hpp>

#include "chat_message.hpp"

using boost::asio::ip::tcp;

std::string lastMessage;
int lastMessageNum = 0;

class chat_client
{
public:
  chat_client(boost::asio::io_service& io_service,
      tcp::resolver::iterator endpoint_iterator)
    : io_service_(io_service),
      socket_(io_service)
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
};

//----------------------------------------------------------------------

void connect(const char* host, const char* port);
void sendMessage(std::string s);
void disconnect();



boost::asio::io_service io_service;
chat_client* client;
std::thread* thread;

int main(int argc, char* argv[])
{
  try
  {
    connect("localhost", "12345");
    sleep(2);
    sendMessage("asdkanclaskdnasdlknxxx");
    sleep(2);
    std::cout << "Message " << lastMessageNum << " " << lastMessage << std::endl;
    sendMessage("yyy");
    sleep(2);
    std::cout << "Message " << lastMessageNum << " " << lastMessage << std::endl;
    std::string s(3000, 'a');
    sendMessage(s);
    sleep(2);
    std::cout << "Message " << lastMessageNum << " " << lastMessage << std::endl;
    disconnect();
    
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

void connect(const char* host, const char* port){
  tcp::resolver resolver(io_service);
  auto endpoint_iterator = resolver.resolve({ host, port });
  client = new chat_client(io_service, endpoint_iterator);
  std::cout << "Connected to chat server on " 
      << endpoint_iterator->endpoint().address() 
      << ":" << endpoint_iterator->endpoint().port() 
      << std::endl;

  thread = new std::thread ([](){ io_service.run(); });

  std::cout << "Start typing your messages!" << std::endl;
  
}

void sendMessage(std::string s){
    try{
    char line[chat_message::MAX_BODY_LENGTH + 1];
    
    if (s.length() > chat_message::MAX_BODY_LENGTH){
      throw std::invalid_argument("invalid string length");
    }

    for (int i = 0; i < s.length(); i++)
    {
      line[i] = s[i];
    }
    line[s.length()] = '\0';
    
    chat_message msg;
    msg.body_length(std::strlen(line));
    std::memcpy(msg.body(), line, msg.body_length());
    msg.encode_header();
    client->write(msg);
    }
    catch (std::exception& e)
    {
    std::cerr << "Exception: " << e.what() << "\n";
    }
    
}

void disconnect(){
  try
  {
    client->close();
    thread->join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

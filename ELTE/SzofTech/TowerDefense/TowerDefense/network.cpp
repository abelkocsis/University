#include "pch.h"
#include "network.h"
#include <iostream>
// #include boost asio and whatever is needed
// put the real network implementation here.


network_interface::network_interface() {
	implementation = new network();
}

network::network()
{
	server = false;
	initialized = false;
	lastAsked = 0;
}


void network::init(bool is_server, const char * s_address, const char * s_port)
{
	server = is_server;
	initialized = true;
	lastAsked = 0;
	if (is_server)
	{
		try {
			tcp::endpoint endpoint(tcp::v4(), std::atoi(s_port));
			servers.emplace_back(io_service_server, endpoint);
			std::cout << "Started chat server on port " << endpoint.port() << std::endl;


			std::cout << "Press Ctrl+C to exit!" << std::endl;
			server_thread = new std::thread([this]() { io_service_server.run(); });
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}
	}
}

void network::connect(const char * host, const char * port)
{
		tcp::resolver resolver(io_service);
		auto endpoint_iterator = resolver.resolve({ host, port });
		client = new chat_client(io_service, endpoint_iterator);
		std::cout << "Connected to chat server on "
			<< endpoint_iterator->endpoint().address()
			<< ":" << endpoint_iterator->endpoint().port()
			<< std::endl;

		thread = new std::thread([this]() { io_service.run(); });

		std::cout << "Start typing your messages!" << std::endl;
}

void network::disconnect()
{
		try
		{
			client->close();
			thread->join();
			/*if (server) {
				delete server_thread;
			}*/
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}
}

void network::send_msg(std::string s)
{
	try {
		char line[chat_message::MAX_BODY_LENGTH + 1];

		if (s.length() > chat_message::MAX_BODY_LENGTH) {
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

bool network::newMessage()
{
	int a = client->get_lastMessageNum();
	return ( a != lastAsked);
}

std::string& network::receive_msg()
{
	int a = client->get_lastMessageNum();
	if (a != lastAsked) 
		lastAsked = a;
	return (client->get_lastMessage());
}

network::~network()
{
	delete client;
	delete thread;
	delete server_thread;
}

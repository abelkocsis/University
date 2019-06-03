#pragma once
#include <string>


class parent_network {
public:
	
	bool is_server;

	virtual void init(bool is_server, const char* s_address, const char* s_port) = 0;

	virtual void connect(const char* host, const char* port) = 0;

	virtual void disconnect() = 0 ;

	virtual void send_msg(std::string s) = 0;

	virtual bool newMessage() = 0;

	virtual std::string& receive_msg() = 0;

};

class network_interface {

public:
	network_interface();
	void init(bool is_server, const char* s_address, const char* s_port) {
		implementation->init(is_server, s_address, s_port);
	}

	void connect(const char* host, const char* port) {
		implementation->connect(host, port);
	}

	void disconnect() {
		implementation->disconnect();
	}

	void send_msg(std::string s) {
		implementation->send_msg(s);
	}

	bool newMessage() {
		return implementation->newMessage();
	}

	std::string& receive_msg() {
		return implementation->receive_msg();
	}



private:
	parent_network* implementation;
};

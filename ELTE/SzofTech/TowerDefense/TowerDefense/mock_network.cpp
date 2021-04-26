#include "network_interface.h"
#include <iostream>

// in this file, only put fake test things. Must have no Boost dependencies!
// also no pch, or windows stuff pls
// these calls should not do anything useful. Write whatever is needed to make tests work / make the model work without a 
// network layer dependency.



class mock_network : public parent_network
{
	 std::string s = "fakenews";
public:

	void init(bool is_server, const char* s_address, const char* s_port) { return;  }

	void connect(const char* host, const char* port) { return;  }

	void disconnect() { return; }

	void send_msg(std::string s) { return; }

	bool newMessage() { return false; }

	std::string& receive_msg() { return s; }


};

network_interface::network_interface() {
	implementation = new mock_network();
}

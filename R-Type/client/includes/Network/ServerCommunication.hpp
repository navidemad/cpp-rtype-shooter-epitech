#pragma once

class ServerCommunication
{
	// ctor - dtor
	public:
		ServerCommunication();
		~ServerCommunication();

	// coplien form
	private:
		ServerCommunication(ServerCommunication const &) {}
		ServerCommunication const	&operator=(ServerCommunication const &) { return *this; }
};

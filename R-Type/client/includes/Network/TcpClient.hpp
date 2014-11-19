#pragma once

class TcpClient
{
	// ctor - dtor
	public:
		TcpClient();
		~TcpClient();

	// coplien form
	private:
		TcpClient(TcpClient const &) {}
		TcpClient const	&operator=(TcpClient const &) { return *this; }
};

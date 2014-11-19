#pragma once

class UdpClient
{
	// ctor - dtor
	public:
		UdpClient();
		~UdpClient();

	// coplien form
	private:
		UdpClient(UdpClient const &) {}
		UdpClient const	&operator=(UdpClient const &) { return *this; }
};

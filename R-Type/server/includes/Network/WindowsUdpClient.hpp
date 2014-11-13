#pragma once

#include "IClientSocket.hpp"

class WindowsUdpClient : public IClientSocket {

	// ctor - dtor
	public:
		WindowsUdpClient(void);
		~WindowsUdpClient(void);

	// copy / move operators
	public:
		WindowsUdpClient(const WindowsUdpClient &) = delete;
		WindowsUdpClient(const WindowsUdpClient &&) = delete;
		const WindowsUdpClient &operator=(const WindowsUdpClient &) = delete;
		const WindowsUdpClient &operator=(const WindowsUdpClient &&) = delete;

};

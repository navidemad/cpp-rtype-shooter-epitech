#pragma once

#include "IClientSocket.hpp"

class WindowsTcpClient : public IClientSocket {

	// ctor - dtor
	public:
		WindowsTcpClient(void);
		~WindowsTcpClient(void);

	// copy / move operators
	public:
		WindowsTcpClient(const WindowsTcpClient &) = delete;
		WindowsTcpClient(const WindowsTcpClient &&) = delete;
		const WindowsTcpClient &operator=(const WindowsTcpClient &) = delete;
		const WindowsTcpClient &operator=(const WindowsTcpClient &&) = delete;

};

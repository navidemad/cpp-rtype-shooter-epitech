#pragma once

#include "IServerSocket.hpp"

class WindowsTcpServer : public IServerSocket {

	// ctor - dtor
	public:
		WindowsTcpServer(void);
		~WindowsTcpServer(void);

	// copy / move operators
	public:
		WindowsTcpServer(const WindowsTcpServer &) = delete;
		WindowsTcpServer(const WindowsTcpServer &&) = delete;
		const WindowsTcpServer &operator=(const WindowsTcpServer &) = delete;
		const WindowsTcpServer &operator=(const WindowsTcpServer &&) = delete;

};

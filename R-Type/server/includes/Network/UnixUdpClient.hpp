#pragma once

#include "IClientSocket.hpp"

class UnixUdpClient : public IClientSocket {

	// ctor - dtor
	public:
		UnixUdpClient(void);
		~UnixUdpClient(void);

	// copy / move operators
	public:
		UnixUdpClient(const UnixUdpClient &) = delete;
		UnixUdpClient(const UnixUdpClient &&) = delete;
		const UnixUdpClient &operator=(const UnixUdpClient &) = delete;
		const UnixUdpClient &operator=(const UnixUdpClient &&) = delete;

};

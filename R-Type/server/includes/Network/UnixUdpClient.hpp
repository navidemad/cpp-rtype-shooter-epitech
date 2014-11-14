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

	// start - stop
	public:
		void	connect(const std::string &addr, int port);
		void	initFromSocket(void *socket, const std::string &addr, int port);
		void	closeClient(void);

	// recv / send
	public:
		void					send(const Message &message);
		Message				receive(unsigned int sizeToRead);
		unsigned int	nbBytesToRead(void) const;

  // get host ip
  public:
		const std::string &getAddr(void) const;

	// set listener
	public:
		void	setOnSocketEventListener(IClientSocket::OnSocketEvent *listener);

};

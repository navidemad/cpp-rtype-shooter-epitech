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

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

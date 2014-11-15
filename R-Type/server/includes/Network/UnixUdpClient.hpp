#pragma once

#include "IClientSocket.hpp"
#include "NetworkManager.hpp"
#include <deque>

class UnixUdpClient : public IClientSocket, public NetworkManager::OnSocketEvent {

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

	// internal functions
	private:
		void	initSocket(void);
		void	bindSocket(int port);
		int 	sendSocket(void);
		void	recvSocket(void);

	// recv / send
	public:
		void					send(const Message &message);
		Message				receive(unsigned int sizeToRead);
		unsigned int	nbBytesToRead(void) const;

    // get host ip
    public:
        const std::string &getAddr(void) const;
        int getPort(void) const;

	// set listener
	public:
		void	setOnSocketEventListener(IClientSocket::OnSocketEvent *listener);

	// NetworkManager callback methods
	public:
		void	onSocketWritable(int socketFd);
		void	onSocketReadable(int socketFd);

	// attributes
	private:
		int mSocketFd;
		std::string mAddr;
		int mPort;
		std::deque<Message> mInDatagrams;
		std::deque<Message> mOutDatagrams;
		std::shared_ptr<IMutex> mMutex;
		IClientSocket::OnSocketEvent *mListener;
		std::shared_ptr<NetworkManager>	mNetworkManager;

};

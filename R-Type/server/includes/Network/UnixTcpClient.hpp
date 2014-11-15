#pragma once

#include <string>
#include <vector>
#include "IMutex.hpp"
#include "IClientSocket.hpp"
#include "NetworkManager.hpp"

class UnixTcpClient : public IClientSocket, public NetworkManager::OnSocketEvent {

	// ctor - dtor
	public:
		UnixTcpClient(void);
		~UnixTcpClient(void);

	// copy / move operators
	public:
		UnixTcpClient(const UnixTcpClient &) = delete;
		UnixTcpClient(const UnixTcpClient &&) = delete;
		const UnixTcpClient &operator=(const UnixTcpClient &) = delete;
		const UnixTcpClient &operator=(const UnixTcpClient &&) = delete;

	// start - stop
	public:
		void	connect(const std::string &addr, int port);
		void	initFromSocket(void *socket, const std::string &addr, int port);
		void	closeClient(void);

	// internal functions
	private:
		void	initSocket(void);
		void	connectSocket(const std::string &addr, int port);
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
		void	onSocketClosed(int socketFd);

	// attributes
	private:
		int mSocketFd;
		std::string mAddr;
		int mPort;
		std::vector<char> mInBuffer;
		std::vector<char> mOutBuffer;
		std::shared_ptr<IMutex> mMutex;
		IClientSocket::OnSocketEvent *mListener;
		std::shared_ptr<NetworkManager>	mNetworkManager;

};

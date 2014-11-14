#pragma once

#include "IServerSocket.hpp"
#include "NetworkManager.hpp"

class UnixTcpServer : public IServerSocket, public NetworkManager::OnSocketEvent {

	// ctor - dtor
	public:
		UnixTcpServer(void);
		~UnixTcpServer(void);

	// copy / move operators
	public:
		UnixTcpServer(const UnixTcpServer &) = delete;
		UnixTcpServer(const UnixTcpServer &&) = delete;
		const UnixTcpServer &operator=(const UnixTcpServer &) = delete;
		const UnixTcpServer &operator=(const UnixTcpServer &&) = delete;

	// init
	public:
		void	createServer(int port, int queueSize);
		void	closeServer(void);

	// intern init
	private:
		void	initSocket(void);
		void	bindSocket(int port);
		void	listenSocket(int queueSize);
		void	acceptClient(int &clientFd, int &clientPort, std::string &clientAddr);

	// listeners
	public:
		void	setOnSocketEventListener(IServerSocket::OnSocketEvent *listener);

	// handle clients
	public:
		std::shared_ptr<IClientSocket>	getNewClient(void);

	// NetworkManager callback methods
	public:
		void	onSocketWritable(int socketFd);
		void	onSocketReadable(int socketFd);
		void	onSocketClosed(int socketFd);

	// attributes
	private:
		int mServerFd;
		IServerSocket::OnSocketEvent *mListener;
		std::shared_ptr<NetworkManager>	mNetworkManager;

};

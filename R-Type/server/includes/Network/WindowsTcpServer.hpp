#pragma once

#include "IServerSocket.hpp"
#include "NetworkManager.hpp"
#include "NoCopyable.hpp"

class WindowsTcpServer : public NoCopyable, public IServerSocket, public NetworkManager::OnSocketEvent {

	// ctor - dtor
	public:
		WindowsTcpServer(void);
		~WindowsTcpServer(void);

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

	// attributes
	private:
		int mServerFd;
		IServerSocket::OnSocketEvent *mListener;
        std::shared_ptr<NetworkManager>	mNetworkManager;

};

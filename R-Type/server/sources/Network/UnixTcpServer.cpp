#include "UnixTcpServer.hpp"
#include "UnixTcpClient.hpp"
#include "SocketException.hpp"
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

UnixTcpServer::UnixTcpServer(void) : mServerFd(-1), mListener(nullptr), mNetworkManager(NetworkManager::getInstance()) {
}

UnixTcpServer::~UnixTcpServer(void) {
	closeServer();
}

void	UnixTcpServer::createServer(int port, int queueSize) {
	closeServer();
	initSocket();
	bindSocket(port);
	listenSocket(queueSize);

	mNetworkManager->addSocket(mServerFd, this);
}

void	UnixTcpServer::initSocket(void) {
	mServerFd = socket(AF_INET, SOCK_STREAM, 0);

	if (mServerFd < 0)
		throw SocketException("fail socket()");
}

void	UnixTcpServer::bindSocket(int port) {
	struct sockaddr_in serverAddr;

	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);

	if (bind(mServerFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
		throw SocketException("fail bind()");
}

void	UnixTcpServer::listenSocket(int queueSize) {
	if (listen(mServerFd, queueSize) < 0)
		throw SocketException("fail listen()");
}

void	UnixTcpServer::closeServer(void) {
	if (mServerFd != -1) {
		mNetworkManager->removeSocket(mServerFd);
		close(mServerFd);
		mServerFd = -1;
	}
}

void	UnixTcpServer::setOnSocketEventListener(IServerSocket::OnSocketEvent *listener) {
	mListener = listener;
}

std::shared_ptr<IClientSocket>	UnixTcpServer::getNewClient(void) {
	int clientFd;
	int clientPort;
	std::string clientAddr;

	acceptClient(clientFd, clientPort, clientAddr);

	std::shared_ptr<IClientSocket> client(new UnixTcpClient);
	client->initFromSocket(&clientFd, clientAddr, clientPort);

	return client;
}

void	UnixTcpServer::acceptClient(int &clientFd, int &clientPort, std::string &clientAddr) {
	struct sockaddr_in addr;
	int clientLen = sizeof(addr);

	clientFd = accept(mServerFd, reinterpret_cast<struct sockaddr *>(&addr), reinterpret_cast<socklen_t *>(&clientLen));
	if (clientFd < 0)
		throw SocketException("fail accept()");

	char ipstr[INET_ADDRSTRLEN + 1];
	if (inet_ntop(AF_INET, &addr.sin_addr, ipstr, sizeof(ipstr)) == NULL)
		throw SocketException("fail inet_ntop()");

	clientPort = ntohs(addr.sin_port);
	clientAddr = ipstr;
}

void	UnixTcpServer::onSocketWritable(int) {
}

void	UnixTcpServer::onSocketReadable(int) {
	if (mListener)
		mListener->onNewConnection(this);
}

void	UnixTcpServer::onSocketClosed(int) {
}

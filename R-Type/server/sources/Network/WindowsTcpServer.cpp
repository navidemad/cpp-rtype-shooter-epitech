#include "WindowsTcpServer.hpp"
#include "WindowsTcpClient.hpp"
#include "SocketException.hpp"
#include "PortabilityBuilder.hpp"
#include "WindowsWSAHandler.hpp"
#include <cstring>

WindowsTcpServer::WindowsTcpServer(void) : mServerFd(-1), mListener(nullptr), mNetworkManager(NetworkManager::getInstance()) {
	WindowsWSAHandler::init();
}

WindowsTcpServer::~WindowsTcpServer(void) {
	closeServer();
	WindowsWSAHandler::cleanup();
}

void	WindowsTcpServer::createServer(int port, int queueSize) {
	closeServer();
	initSocket();
	bindSocket(port);
	listenSocket(queueSize);

	mNetworkManager->addSocket(mServerFd, this);
}

void	WindowsTcpServer::initSocket(void) {
	mServerFd = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 0);

	if (mServerFd == INVALID_SOCKET)
		throw SocketException("fail WSASocket()");
}

void	WindowsTcpServer::bindSocket(int port) {
	struct sockaddr_in serverAddr;

	std::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);

	if (bind(mServerFd, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
		throw SocketException("fail bind() tcp");
}

void	WindowsTcpServer::listenSocket(int queueSize) {
	if (listen(mServerFd, queueSize) == SOCKET_ERROR)
		throw SocketException("fail listen()");
}

void	WindowsTcpServer::closeServer(void) {
	if (mServerFd != -1) {
		mNetworkManager->removeSocket(mServerFd);
		closesocket(mServerFd);
		mServerFd = -1;
	}
}

void	WindowsTcpServer::setOnSocketEventListener(IServerSocket::OnSocketEvent *listener) {
	mListener = listener;
}

std::shared_ptr<IClientSocket>	WindowsTcpServer::getNewClient(void) {
	int clientFd;
	int clientPort;
	std::string clientAddr;

	acceptClient(clientFd, clientPort, clientAddr);

	std::shared_ptr<IClientSocket> client = PortabilityBuilder::getTcpClient();
	client->initFromSocket(&clientFd, clientAddr, clientPort);

	return client;
}

void	WindowsTcpServer::acceptClient(int &clientFd, int &clientPort, std::string &clientAddr) {
	struct sockaddr_in addr;
	int clientLen = sizeof(addr);

	clientFd = WSAAccept(mServerFd, reinterpret_cast<struct sockaddr *>(&addr), &clientLen, NULL, NULL);
	if (clientFd == INVALID_SOCKET)
		throw SocketException("fail WSAAccept()");

	char *ipstr = inet_ntoa(addr.sin_addr);
	if (ipstr == NULL)
		throw SocketException("fail inet_ntoa()");

	clientPort = ntohs(addr.sin_port);
	clientAddr = ipstr;
}

void	WindowsTcpServer::onSocketWritable(int) {
}

void	WindowsTcpServer::onSocketReadable(int) {
	if (mListener)
		mListener->onNewConnection(this);
}

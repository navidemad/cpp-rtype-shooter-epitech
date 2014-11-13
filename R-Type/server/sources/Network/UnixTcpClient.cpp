#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <cstring>
#include "UnixTcpClient.hpp"
#include "SocketException.hpp"

UnixTcpClient::UnixTcpClient(void) : mSocketFd(-1), mAddr(""), mPort(-1), mListener(nullptr), mNetworkManager(NetworkManager::getInstance()) {
}

UnixTcpClient::~UnixTcpClient(void) {
}

void	UnixTcpClient::connect(const std::string &addr, int port) {
	closeClient();
	initSocket();
	connectSocket(addr, port);

	mAddr = addr;
	mPort = port;

	mNetworkManager->addSocket(mSocketFd, this);
}

void	UnixTcpClient::initSocket(void) {
  mSocketFd = socket(AF_INET, SOCK_STREAM, 0);

  if (mSocketFd == -1)
  	throw SocketException("fail socket()");
}

void	UnixTcpClient::connectSocket(const std::string &addr, int port) {
  struct sockaddr_in serv_addr; 

  memset(&serv_addr, 0, sizeof(serv_addr)); 
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, addr.c_str(), &serv_addr.sin_addr) == -1)
  	throw SocketException("fail inet_pton()");

  if(::connect(mSocketFd, reinterpret_cast<struct sockaddr *>(&serv_addr), sizeof(serv_addr)) == -1)
  	throw SocketException("fail connect()");
}

void	UnixTcpClient::initFromSocket(void *socketFd, const std::string &addr, int port) {
	mSocketFd = *reinterpret_cast<int *>(socketFd);
	mAddr = addr;
	mPort = port;
}

void	UnixTcpClient::closeClient(void) {
	if (mSocketFd != -1) {
		mNetworkManager->removeSocket(mSocketFd);
		close(mSocketFd);

		mSocketFd = -1;
		mAddr = "";
		mPort = -1;
	}
}

void	UnixTcpClient::send(const IClientSocket::Message &message) {
}

IClientSocket::Message	UnixTcpClient::receive(unsigned int sizeToRead) {
}

unsigned int	UnixTcpClient::nbBytesToRead(void) const {
	return mBuffer.size();
}

const std::string &UnixTcpClient::getAddr(void) const {
	return mAddr;
}

int UnixTcpClient::getPort(void) const {
	return mPort;
}

void	UnixTcpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *listener) {
	mListener = listener;
}

void	UnixTcpClient::onBytesWritten(int, unsigned int nbBytes) {
	if (mListener)
		mListener->onBytesWritten(this, nbBytes);
}

void	UnixTcpClient::onSocketReadable(int) {
	if (mListener)
		mListener->onSocketReadable(this, mBuffer.size());
}

void	UnixTcpClient::onSocketClosed(int) {
	if (mListener)
		mListener->onSocketClosed(this);
}

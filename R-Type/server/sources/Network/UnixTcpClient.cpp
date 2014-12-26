#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <cstring>
#include "ScopedLock.hpp"
#include "PortabilityBuilder.hpp"
#include "UnixTcpClient.hpp"
#include "SocketException.hpp"

UnixTcpClient::UnixTcpClient(void)
	: mSocketFd(-1), mAddr(""), mPort(-1),
		mMutex(PortabilityBuilder::getMutex()), mListener(nullptr), mNetworkManager(NetworkManager::getInstance())
{}

UnixTcpClient::~UnixTcpClient(void) {
	closeClient();
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

	mNetworkManager->addSocket(mSocketFd, this);
}

void	UnixTcpClient::closeClient(void) {
	ScopedLock scopedlock(mMutex);;

	if (mSocketFd != -1) {
		mNetworkManager->removeSocket(mSocketFd);
		close(mSocketFd);

		mSocketFd = -1;
		mAddr = "";
		mPort = -1;
		mInBuffer.clear();
		mOutBuffer.clear();
	}
}

void	UnixTcpClient::send(const IClientSocket::Message &message) {
	ScopedLock scopedlock(mMutex);;

	mOutBuffer.insert(mOutBuffer.end(), message.msg.begin(), message.msg.end());
}

IClientSocket::Message	UnixTcpClient::receive(unsigned int sizeToRead) {
	ScopedLock scopedlock(mMutex);;

	IClientSocket::Message message;

	if (sizeToRead > mInBuffer.size())
		sizeToRead = mInBuffer.size();

	std::copy(mInBuffer.begin(), mInBuffer.begin() + sizeToRead, back_inserter(message.msg));
	mInBuffer.erase(mInBuffer.begin(), mInBuffer.begin() + sizeToRead);
	message.msgSize = sizeToRead;

	return message;
}

unsigned int	UnixTcpClient::nbBytesToRead(void) const {
	ScopedLock scopedlock(mMutex);;

	return mInBuffer.size();
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

void	UnixTcpClient::onSocketWritable(int) {
	try {
		int nbBytes = sendSocket();

        if (mListener && nbBytes)
			mListener->onBytesWritten(this, nbBytes);
	}
	catch (const SocketException &) {
		closeClient();

		if (mListener)
			mListener->onSocketClosed(this);
	}
}

int UnixTcpClient::sendSocket(void) {
	ScopedLock scopedlock(mMutex);;

    if (mOutBuffer.size() == 0)
        return 0;

    int sizeToSend = mOutBuffer.size() > 1024 ? 1024 : mOutBuffer.size();
	int nbBytesSent = ::send(mSocketFd, mOutBuffer.data(), sizeToSend, MSG_NOSIGNAL);

	if (nbBytesSent == -1)
		throw SocketException("Fail send()");

	mOutBuffer.erase(mOutBuffer.begin(), mOutBuffer.begin() + nbBytesSent);

	return nbBytesSent;
}

void UnixTcpClient::recvSocket(void) {
	ScopedLock scopedlock(mMutex);;

	char buffer[1024];
	int nbBytesRead = ::recv(mSocketFd, buffer, 1024, 0);

	if (nbBytesRead == -1)
		throw SocketException("fail recv()");
	else if (nbBytesRead == 0)
		throw SocketException("connection closed");

	mInBuffer.insert(mInBuffer.end(), buffer, buffer + nbBytesRead);
}

void	UnixTcpClient::onSocketReadable(int) {
	try {
		recvSocket();

		if (mListener)
			mListener->onSocketReadable(this, nbBytesToRead());
	}
	catch (const SocketException &) {
		closeClient();

		if (mListener)
			mListener->onSocketClosed(this);
	}
}

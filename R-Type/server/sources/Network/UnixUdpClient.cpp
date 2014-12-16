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
#include "UnixUdpClient.hpp"
#include "SocketException.hpp"

UnixUdpClient::UnixUdpClient(void)
	: mSocketFd(-1), mAddr(""), mPort(-1),
		mMutex(PortabilityBuilder::getMutex()), mListener(nullptr), mNetworkManager(NetworkManager::getInstance())
{}

UnixUdpClient::~UnixUdpClient(void) {
	closeClient();
}

void	UnixUdpClient::connect(const std::string &addr, int port) {
	closeClient();
	initSocket();
	bindSocket(port);

	mAddr = addr;
	mPort = port;

	mNetworkManager->addSocket(mSocketFd, this);
}

void	UnixUdpClient::initSocket(void) {
  mSocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (mSocketFd == -1)
  	throw SocketException("fail socket()");
}

void	UnixUdpClient::bindSocket(int port) {
	struct sockaddr_in clientAddr;

	bzero(&clientAddr, sizeof(clientAddr));
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr.s_addr = INADDR_ANY;
	clientAddr.sin_port = htons(port);

	if (bind(mSocketFd, reinterpret_cast<struct sockaddr *>(&clientAddr), sizeof(clientAddr)) < 0)
		throw SocketException("fail bind()");
}

void	UnixUdpClient::initFromSocket(void *socketFd, const std::string &addr, int port) {
	mSocketFd = *reinterpret_cast<int *>(socketFd);
	mAddr = addr;
	mPort = port;

	mNetworkManager->addSocket(mSocketFd, this);
}

void	UnixUdpClient::closeClient(void) {
	Scopedlock(mMutex);

	if (mSocketFd != -1) {
		mNetworkManager->removeSocket(mSocketFd);
		close(mSocketFd);

		mSocketFd = -1;
		mAddr = "";
		mPort = -1;
		mInDatagrams.clear();
		mOutDatagrams.clear();
	}
}

void	UnixUdpClient::send(const IClientSocket::Message &message) {
	Scopedlock(mMutex);

	mOutDatagrams.push_back(message);
}

IClientSocket::Message	UnixUdpClient::receive(unsigned int sizeToRead) {
	Scopedlock(mMutex);
	
	if (mInDatagrams.size() == 0)
		throw SocketException("No datagrams available");

	IClientSocket::Message message;

	if (mInDatagrams.front().msgSize <= sizeToRead) {
		message = mInDatagrams.front();
		mInDatagrams.pop_front();
	}
	else {
		IClientSocket::Message &datagram = mInDatagrams.front();

		message.msg.insert(message.msg.end(), datagram.msg.begin(), datagram.msg.begin() + sizeToRead);		
		message.msgSize = sizeToRead;
		message.host = datagram.host;
		message.port = datagram.port;

		datagram.msg.erase(datagram.msg.begin(), datagram.msg.begin() + sizeToRead);
		datagram.msgSize -= sizeToRead;
	}

	return message;
}

unsigned int	UnixUdpClient::nbBytesToRead(void) const {
	Scopedlock(mMutex);
	
	if (mInDatagrams.size() == 0)
		return 0;

	std::cout << "mInDatagrams.front().msgSize: " << mInDatagrams.front().msgSize << std::endl;
	return mInDatagrams.front().msgSize;
}

const std::string &UnixUdpClient::getAddr(void) const {
	return mAddr;
}

int UnixUdpClient::getPort(void) const {
	return mPort;
}

void	UnixUdpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *listener) {
	mListener = listener;
}

void	UnixUdpClient::onSocketWritable(int) {
	try {
		int nbBytes = sendSocket();

        if (mListener && nbBytes)
			mListener->onBytesWritten(this, nbBytes);
	}
	catch (const SocketException &) {
	}
}

int UnixUdpClient::sendSocket(void) {
	Scopedlock(mMutex);

    if (mOutDatagrams.size() == 0)
        return 0;

  IClientSocket::Message message = mOutDatagrams.front();
	mOutDatagrams.pop_front();

	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(message.port);
  if (inet_aton(message.host.c_str(), &addr.sin_addr) == 0)
  	throw SocketException("Fail inet_aton()");

	int nbBytesSent = ::sendto(mSocketFd, message.msg.data(), message.msgSize, MSG_NOSIGNAL,  reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr));

	if (nbBytesSent == -1)
		throw SocketException("Fail send()");

	return nbBytesSent;
}

void UnixUdpClient::recvSocket(void) {
	Scopedlock(mMutex);

	char buffer[1024];
	struct sockaddr_in addr;
	socklen_t size = sizeof(addr);
	int nbBytesRead = ::recvfrom(mSocketFd, buffer, 1024, 0,  reinterpret_cast<struct sockaddr *>(&addr), &size);

	if (nbBytesRead == -1)
		throw SocketException("fail recv()");

	std::string host = inet_ntoa(addr.sin_addr);
	int port = ntohs(addr.sin_port);

	if (mInDatagrams.size() == 0 || mInDatagrams.back().host != host || mInDatagrams.back().port != port) {
		IClientSocket::Message message;

		message.msgSize = 0;
		message.host = host;
		message.port = port;

		mInDatagrams.push_back(message);
	}

	mInDatagrams.back().msg.insert(mInDatagrams.back().msg.end(), buffer, buffer + nbBytesRead);
	mInDatagrams.back().msgSize += nbBytesRead;
}

void	UnixUdpClient::onSocketReadable(int) {
	try {
		recvSocket();

		if (mListener)
			mListener->onSocketReadable(this, nbBytesToRead());
	}
	catch (const SocketException &) {
	}
}

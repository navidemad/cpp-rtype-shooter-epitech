#include <cstring>
#include <WS2tcpip.h>
#include "ScopedLock.hpp"
#include "PortabilityBuilder.hpp"
#include "WindowsUdpClient.hpp"
#include "SocketException.hpp"
#include "WindowsWSAHandler.hpp"

WindowsUdpClient::WindowsUdpClient(void)
: mSocketFd(-1), mAddr(""), mPort(-1),
mMutex(PortabilityBuilder::getMutex()), mListener(nullptr), mNetworkManager(NetworkManager::getInstance())
{
	WindowsWSAHandler::init();
}

WindowsUdpClient::~WindowsUdpClient(void) {
	closeClient();
	WindowsWSAHandler::cleanup();
}

void	WindowsUdpClient::connect(const std::string &addr, int port) {
	closeClient();
	initSocket();
	bindSocket(port);

	mAddr = addr;
	mPort = port;

	mNetworkManager->addSocket(mSocketFd, this);
}

void	WindowsUdpClient::initSocket(void) {
	mSocketFd = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0);

	if (mSocketFd == INVALID_SOCKET)
		throw SocketException("fail WSASocket()");
}

void	WindowsUdpClient::bindSocket(int port) {
	struct sockaddr_in clientAddr;

	std::memset(&clientAddr, 0, sizeof(clientAddr));
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr.s_addr = INADDR_ANY;
	clientAddr.sin_port = htons(port);

	if (bind(mSocketFd, reinterpret_cast<struct sockaddr *>(&clientAddr), sizeof(clientAddr)) < 0)
		throw SocketException("fail bind() udp");
}

void	WindowsUdpClient::initFromSocket(void *socketFd, const std::string &addr, int port) {
	mSocketFd = *reinterpret_cast<int *>(socketFd);
	mAddr = addr;
	mPort = port;

	mNetworkManager->addSocket(mSocketFd, this);
}

void	WindowsUdpClient::closeClient(void) {
    ScopedLock scopedlock(mMutex);

	if (mSocketFd != -1) {
		mNetworkManager->removeSocket(mSocketFd);
		closesocket(mSocketFd);

		mSocketFd = -1;
		mAddr = "";
		mPort = -1;
		mInDatagrams.clear();
		mOutDatagrams.clear();
	}
}

void	WindowsUdpClient::send(const IClientSocket::Message &message) {
	ScopedLock scopedlock(mMutex);

	mOutDatagrams.push_back(message);
}

IClientSocket::Message	WindowsUdpClient::receive(unsigned int sizeToRead) {
	ScopedLock scopedlock(mMutex);

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

unsigned int	WindowsUdpClient::nbBytesToRead(void) const {
	ScopedLock scopedlock(mMutex);

	if (mInDatagrams.size() == 0)
		return 0;

	return mInDatagrams.front().msgSize;
}

const std::string &WindowsUdpClient::getAddr(void) const {
	return mAddr;
}

int WindowsUdpClient::getPort(void) const {
	return mPort;
}

void	WindowsUdpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *listener) {
	mListener = listener;
}

void	WindowsUdpClient::onSocketWritable(int) {
	try {
		int nbBytes = sendSocket();

		if (mListener && nbBytes)
			mListener->onBytesWritten(this, nbBytes);
	}
	catch (const SocketException &) {
	}
}

int WindowsUdpClient::sendSocket(void) {
	ScopedLock scopedlock(mMutex);

	if (mOutDatagrams.size() == 0)
		return 0;

	IClientSocket::Message message = mOutDatagrams.front();
	mOutDatagrams.pop_front();

	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(message.port);

	std::wstring saddr = std::wstring(message.host.begin(), message.host.end());
	if (InetPton(AF_INET, saddr.c_str(), &addr.sin_addr) <= 0)
		throw SocketException("fail InetPton()");

	DWORD nbBytesSent;
	WSABUF buf = { message.msgSize, message.msg.data() };

	if (WSASendTo(mSocketFd, &buf, 1, &nbBytesSent, 0, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr), NULL, NULL) == SOCKET_ERROR)
		throw SocketException("Fail send()");

	return nbBytesSent;
}

void WindowsUdpClient::recvSocket(void) {
	ScopedLock scopedlock(mMutex);

	char buffer[1024];
	WSABUF buf = { 1024, buffer };
	struct sockaddr_in addr;
	socklen_t size = sizeof(addr);
	DWORD nbBytesRead;
	DWORD flags = 0;
	if (WSARecvFrom(mSocketFd, &buf, 1, &nbBytesRead, &flags, reinterpret_cast<struct sockaddr *>(&addr), &size, NULL, NULL) == SOCKET_ERROR)
		throw SocketException("fail recv()");

	char *ipstr = inet_ntoa(addr.sin_addr);
	if (ipstr == NULL)
		throw SocketException("fail inet_ntoa()");

	IClientSocket::Message message;
	message.msgSize = nbBytesRead;
	if (mInDatagrams.size())
		message.msg.insert(mInDatagrams.back().msg.end(), buffer, buffer + nbBytesRead);
	else
		message.msg.assign(buffer, buffer + nbBytesRead);
	message.host = ipstr;
	message.port = ntohs(addr.sin_port);
	mInDatagrams.push_back(message);
}

void	WindowsUdpClient::onSocketReadable(int) {
	try {
		recvSocket();

		if (mListener)
			mListener->onSocketReadable(this, nbBytesToRead());
	}
	catch (const SocketException &) {
	}
}

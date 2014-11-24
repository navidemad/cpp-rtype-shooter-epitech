#include <cstring>
#include <Ws2tcpip.h>
#include <winsock2.h>
#include "ScopedLock.hpp"
#include "WindowsWSAHandler.hpp"
#include "PortabilityBuilder.hpp"
#include "WindowsTcpClient.hpp"
#include "SocketException.hpp"

WindowsTcpClient::WindowsTcpClient(void)
	: mSocketFd(-1), mAddr(""), mPort(-1), mMutex(PortabilityBuilder::getMutex()), mListener(nullptr), mNetworkManager(NetworkManager::getInstance())
{
	WindowsWSAHandler::init();
}

WindowsTcpClient::~WindowsTcpClient(void) {
	WindowsWSAHandler::cleanup();
}

void	WindowsTcpClient::connect(const std::string &addr, int port) {
	closeClient();
	initSocket();
	connectSocket(addr, port);

	mAddr = addr;
	mPort = port;

	mNetworkManager->addSocket(mSocketFd, this);
}

void	WindowsTcpClient::initSocket(void) {
	mSocketFd = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 0);

	if (mSocketFd == INVALID_SOCKET)
		throw SocketException("fail WSASocket()");
}

void	WindowsTcpClient::connectSocket(const std::string &addr, int port) {
	struct sockaddr_in serv_addr;

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	std::wstring saddr = std::wstring(addr.begin(), addr.end());
	if (InetPton(AF_INET, saddr.c_str(), &serv_addr.sin_addr) <= 0)
		throw SocketException("fail InetPton()");

	if (WSAConnect(mSocketFd, reinterpret_cast<struct sockaddr *>(&serv_addr), sizeof(serv_addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
		throw SocketException("fail WSAConnect()");
}

void	WindowsTcpClient::initFromSocket(void *socketFd, const std::string &addr, int port) {
	mSocketFd = *reinterpret_cast<int *>(socketFd);
	mAddr = addr;
	mPort = port;

	mNetworkManager->addSocket(mSocketFd, this);
}

void	WindowsTcpClient::closeClient(void) {
	ScopedLock ScopedLock(mMutex);

	if (mSocketFd != -1) {
		mNetworkManager->removeSocket(mSocketFd);
		closesocket(mSocketFd);

		mSocketFd = -1;
		mAddr = "";
		mPort = -1;
		mInBuffer.clear();
		mOutBuffer.clear();
	}
}

void	WindowsTcpClient::send(const IClientSocket::Message &message) {
	ScopedLock ScopedLock(mMutex);

	mOutBuffer.insert(mOutBuffer.end(), message.msg.begin(), message.msg.end());
}

IClientSocket::Message	WindowsTcpClient::receive(unsigned int sizeToRead) {
	ScopedLock ScopedLock(mMutex);

	IClientSocket::Message message;

	if (sizeToRead > mInBuffer.size())
		sizeToRead = mInBuffer.size();

	std::copy(mInBuffer.begin(), mInBuffer.begin() + sizeToRead, back_inserter(message.msg));
	mInBuffer.erase(mInBuffer.begin(), mInBuffer.begin() + sizeToRead);
	message.msgSize = sizeToRead;

	return message;
}

unsigned int	WindowsTcpClient::nbBytesToRead(void) const {
	ScopedLock ScopedLock(mMutex);

	return mInBuffer.size();
}

const std::string &WindowsTcpClient::getAddr(void) const {
	return mAddr;
}

int WindowsTcpClient::getPort(void) const {
	return mPort;
}

void	WindowsTcpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *listener) {
	mListener = listener;
}

void	WindowsTcpClient::onSocketWritable(int) {
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

int WindowsTcpClient::sendSocket(void) {
	ScopedLock ScopedLock(mMutex);

	if (mOutBuffer.size() == 0)
		return 0;

	int sizeToSend = mOutBuffer.size() > 1024 ? 1024 : mOutBuffer.size();
	WSABUF buf = { sizeToSend, mOutBuffer.data() };
	DWORD nbBytesSent;
	
	if (WSASend(mSocketFd, &buf, 1, &nbBytesSent, 0, NULL, NULL) == SOCKET_ERROR)
		throw SocketException("Fail send()");

	mOutBuffer.erase(mOutBuffer.begin(), mOutBuffer.begin() + nbBytesSent);

	return nbBytesSent;
}

void WindowsTcpClient::recvSocket(void) {
	ScopedLock ScopedLock(mMutex);

	char buffer[1024];
	WSABUF buf = { 1024, buffer };
	DWORD nbBytesRead;
	DWORD flags = 0;
	
	if (WSARecv(mSocketFd, &buf, 1, &nbBytesRead, &flags, NULL, NULL) == SOCKET_ERROR)
		throw SocketException("fail recv()");
	else if (nbBytesRead == 0)
		throw SocketException("connection closed");

	mInBuffer.insert(mInBuffer.end(), buffer, buffer + nbBytesRead);
}

void	WindowsTcpClient::onSocketReadable(int) {
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

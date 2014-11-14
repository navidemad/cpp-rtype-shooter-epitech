#include "NetworkManager.hpp"
#include "SocketException.hpp"
#include <algorithm>
#include <sys/types.h>
#include <sys/socket.h>

std::shared_ptr<NetworkManager> NetworkManager::mInstance = nullptr;

NetworkManager::NetworkManager(void) : mMaxFd(-1) {
}

NetworkManager::~NetworkManager(void) {
}

std::list<std::pair<int, NetworkManager::OnSocketEvent *>>::iterator NetworkManager::findSocket(int socketFd) {
	return std::find_if(mSockets.begin(), mSockets.end(), [&](const std::pair<int, NetworkManager::OnSocketEvent *> &socket) { return socket.first == socketFd; });
}

void	NetworkManager::addSocket(int socketFd, NetworkManager::OnSocketEvent *listener) {
	if (socketFd == -1)
		throw SocketException("Invalid socket cannot be under the NetworkManager control");
 
	if (findSocket(socketFd) != mSockets.end())
		throw SocketException("Socket already under NetworkManager control");

	mSockets.push_back(std::pair<int, NetworkManager::OnSocketEvent *>(socketFd, listener));

	if (socketFd > mMaxFd)
		mMaxFd = socketFd;

	if (mSockets.size() == 1)
		startThread();
}

void	NetworkManager::removeSocket(int socketFd) {
	auto socket = findSocket(socketFd);

	if (socket == mSockets.end())
		throw SocketException("Socket is not under the NetworkManager control");

	mSockets.erase(socket);

	if (socketFd == mMaxFd)
		refreshMaxFd();
}

void 	NetworkManager::refreshMaxFd(void) {
	mMaxFd = -1;

	for (const auto &socket : mSockets)
		if (socket.first > mMaxFd)
			mMaxFd = socket.first;
}

std::shared_ptr<NetworkManager> NetworkManager::getInstance(void) {
	if (mInstance.get() != nullptr)
		return mInstance;

	return std::shared_ptr<NetworkManager>(new NetworkManager);
}

int	NetworkManager::receive(int socketFd, char *buffer, int sizeToRead) {
	auto socket = findSocket(socketFd);

	if (socket == mSockets.end())
		throw SocketException("Socket is not under the NetworkManager control");

	int nbBytesRead = ::recv(socketFd, buffer, sizeToRead, 0);

	if (nbBytesRead == -1)
		throw SocketException("fail recv()");

	return nbBytesRead;
}

int	NetworkManager::send(int socketFd, char *buffer, int sizeToWrite) {
	auto socket = findSocket(socketFd);

	if (socket == mSockets.end())
		throw SocketException("Socket is not under the NetworkManager control");

	int nbBytesSent = ::send(socketFd, buffer, sizeToWrite, MSG_NOSIGNAL);

	if (nbBytesSent == -1)
		throw SocketException("Fail send()");

	return nbBytesSent;
}

void	NetworkManager::run(void) {
	while (mSockets.size() > 0) {
		initFds();

		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		if (select(mMaxFd + 1, &mReadFds, &mWriteFds, NULL, &tv) == -1)
			throw SocketException("fail select()");

		checkFds();
	}
}

void	NetworkManager::initFds(void) {
	FD_ZERO(&mReadFds);
	FD_ZERO(&mWriteFds);

	for (const auto &socket : mSockets) {
		FD_SET(socket.first, &mReadFds);
		FD_SET(socket.first, &mWriteFds);
	}
}

void	NetworkManager::checkFds(void) {
	for (const auto &socket : mSockets) {
		if (socket.second == nullptr)
			continue;

		if (FD_ISSET(socket.first, &mReadFds)) {
			if (stillConnected(socket))
				socket.second->onSocketReadable(socket.first);
			else
				socket.second->onSocketClosed(socket.first);
		}

		if (FD_ISSET(socket.first, &mWriteFds))
			socket.second->onSocketWritable(socket.first);
	}
}

#include <pthread.h>
void *pthreadCallback(void *data) {
	reinterpret_cast<NetworkManager *>(data)->run();
	pthread_exit(NULL);
}

void	NetworkManager::startThread(void) {
	pthread_t thread;
	pthread_create(&thread, NULL, pthreadCallback, this);
}

bool	NetworkManager::stillConnected(const std::pair<int, NetworkManager::OnSocketEvent *> &socket) {
	char c;

	return !!::recv(socket.first, &c, 1, MSG_PEEK);
}

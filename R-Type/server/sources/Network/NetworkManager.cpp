#include "NetworkManager.hpp"
#include "SocketException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include <algorithm>
#include <sys/types.h>
#include <sys/socket.h>

std::shared_ptr<NetworkManager> NetworkManager::mInstance = nullptr;

NetworkManager::NetworkManager(void) : mMaxFd(-1), mMutex(PortabilityBuilder::getMutex()) {
}

NetworkManager::~NetworkManager(void) {
}

std::list<std::pair<int, NetworkManager::OnSocketEvent *>>::iterator NetworkManager::findSocket(int socketFd) {
	return std::find_if(mSockets.begin(), mSockets.end(), [&](const std::pair<int, NetworkManager::OnSocketEvent *> &socket) { return socket.first == socketFd; });
}

void	NetworkManager::addSocket(int socketFd, NetworkManager::OnSocketEvent *listener) {
	ScopedLock scopedLock(mMutex);

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
	ScopedLock scopedLock(mMutex);

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
	if (mInstance.get() == nullptr)
		mInstance = std::shared_ptr<NetworkManager>(new NetworkManager);

	return mInstance;
}

int	NetworkManager::receive(int socketFd, char *buffer, int sizeToRead) {
	int nbBytesRead = ::recv(socketFd, buffer, sizeToRead, 0);

	if (nbBytesRead == -1)
		throw SocketException("fail recv()");
	else if (nbBytesRead == 0)
		throw SocketException("connection closed");

	return nbBytesRead;
}

int	NetworkManager::send(int socketFd, char *buffer, int sizeToWrite) {
	int nbBytesSent = ::send(socketFd, buffer, sizeToWrite, MSG_NOSIGNAL);

	if (nbBytesSent == -1)
		throw SocketException("Fail send()");

	return nbBytesSent;
}

void	NetworkManager::run(void) {
	while (mSockets.size() > 0) {
		initFds();

		struct timeval tv;
		tv.tv_sec = 0; /* TO CHANGE */
		tv.tv_usec = 0;
		if (select(mMaxFd + 1, &mReadFds, &mWriteFds, NULL, &tv) == -1)
			throw SocketException("fail select()");

		checkFds();
	}
}

void	NetworkManager::initFds(void) {
	ScopedLock scopedLock(mMutex);

	FD_ZERO(&mReadFds);
	FD_ZERO(&mWriteFds);

	for (const auto &socket : mSockets) {
		FD_SET(socket.first, &mReadFds);
		FD_SET(socket.first, &mWriteFds);
	}
}

void	NetworkManager::checkFds(void) {
	std::list<std::pair<int, NetworkManager::OnSocketEvent *>> sockets;
	{
		ScopedLock scopedLock(mMutex);
		sockets = mSockets;
	}

	for (const auto &socket : sockets) {
		if (socket.second == nullptr)
			continue;

		if (FD_ISSET(socket.first, &mReadFds))
			socket.second->onSocketReadable(socket.first);

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

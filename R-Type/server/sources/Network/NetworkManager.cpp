#include "NetworkManager.hpp"
#include "SocketException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include <algorithm>

NetworkManager::NetworkManager(void) : mMaxFd(-1), mMutex(PortabilityBuilder::getMutex()), mThreadPool(ThreadPool::getInstance()) {
}

NetworkManager::~NetworkManager(void) {
}

std::list<NetworkManager::Socket>::iterator NetworkManager::findSocket(int socketFd) {
	return std::find_if(mSockets.begin(), mSockets.end(), [&](const NetworkManager::Socket &socket) { return socket.fd == socketFd; });
}

void	NetworkManager::addSocket(int socketFd, NetworkManager::OnSocketEvent *listener) {
	ScopedLock scopedLock(mMutex);

	if (socketFd == -1)
		throw SocketException("Invalid socket cannot be under the NetworkManager control");

	if (findSocket(socketFd) != mSockets.end())
		throw SocketException("Socket already under NetworkManager control");

	mSockets.push_back(Socket(socketFd, listener));

	if (socketFd > mMaxFd)
		mMaxFd = socketFd;

	if (mSockets.size() == 1)
		*mThreadPool << std::bind(&NetworkManager::doSelect, this);
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
		if (socket.fd > mMaxFd)
			mMaxFd = socket.fd;
}

std::shared_ptr<NetworkManager> NetworkManager::getInstance(void) {
	static std::shared_ptr<NetworkManager> instance(new NetworkManager);

	return instance;
}

void	NetworkManager::doSelect(void) {
	while (mSockets.size() > 0) {
		initFds();

		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 500;
		if (select(mMaxFd + 1, &mReadFds, &mWriteFds, NULL, &tv) > 0)
			checkFds();
	}
}

void	NetworkManager::initFds(void) {
	ScopedLock scopedLock(mMutex);

	FD_ZERO(&mReadFds);
	FD_ZERO(&mWriteFds);

	for (const auto &socket : mSockets) {
		FD_SET(socket.fd, &mReadFds);
		FD_SET(socket.fd, &mWriteFds);
	}
}

void	NetworkManager::checkFds(void) {
	ScopedLock scopedLock(mMutex);

	for (auto &socket : mSockets) {
		if (!socket.isCurrentlyNotifyRead && socket.listener && FD_ISSET(socket.fd, &mReadFds)) {
			socket.isCurrentlyNotifyRead = true;
			*mThreadPool << std::bind(&NetworkManager::onSocketReadable, this, socket.fd);
		}

		if (!socket.isCurrentlyNotifyWrite && socket.listener && FD_ISSET(socket.fd, &mWriteFds)) {
			socket.isCurrentlyNotifyWrite = true;
			*mThreadPool << std::bind(&NetworkManager::onSocketWritable, this, socket.fd);
		}
	}
}

void	NetworkManager::onSocketReadable(int socketFd) {
	std::list<NetworkManager::Socket>::iterator socket;

	{
		ScopedLock scopedLock(mMutex);

		socket = findSocket(socketFd);
		if (socket == mSockets.end())
			return;
	}

	socket->listener->onSocketReadable(socket->fd);

	{
		ScopedLock scopedLock(mMutex);

		socket = findSocket(socketFd);
		if (socket == mSockets.end())
			return;

		socket->isCurrentlyNotifyRead = false;
	}
}

void	NetworkManager::onSocketWritable(int socketFd) {
	std::list<NetworkManager::Socket>::iterator socket;

	{
		ScopedLock scopedLock(mMutex);

		socket = findSocket(socketFd);
		if (socket == mSockets.end())
			return;
	}

	socket->listener->onSocketWritable(socket->fd);

	{
		ScopedLock scopedLock(mMutex);

		socket = findSocket(socketFd);
		if (socket == mSockets.end())
			return;

		socket->isCurrentlyNotifyWrite = false;
	}
}

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
		return;

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
		bool readable = FD_ISSET(socket.fd, &mReadFds) != 0;
		bool writable = FD_ISSET(socket.fd, &mWriteFds) != 0;

		if ((readable || writable) && !socket.isCallbackRunning && socket.listener) {
			socket.isCallbackRunning = true;
			*mThreadPool << std::bind(&NetworkManager::socketCallback, this, socket.fd, readable, writable);
		}
	}
}

void	NetworkManager::socketCallback(int socketFd, bool readable, bool writable) {
	std::list<NetworkManager::Socket>::iterator socket;
	{
		ScopedLock scopedLock(mMutex);

		socket = findSocket(socketFd);
	}

	if (readable && stillUnderControl(socketFd))
		socket->listener->onSocketReadable(socket->fd);

	if (writable && stillUnderControl(socketFd))
		socket->listener->onSocketWritable(socket->fd);

	if (stillUnderControl(socketFd))
		socket->isCallbackRunning = false;
}

bool NetworkManager::stillUnderControl(int socketFd) {
	ScopedLock scopedLock(mMutex);

	return findSocket(socketFd) != mSockets.end();
}

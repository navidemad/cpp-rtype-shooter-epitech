#include "NetworkManager.hpp"
#include "SocketException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include <algorithm>

std::shared_ptr<NetworkManager> NetworkManager::mInstance = nullptr;

NetworkManager::NetworkManager(void) : mMaxFd(-1), mMutex(PortabilityBuilder::getMutex()), mThread(PortabilityBuilder::getThread<NetworkManager *, void*>()) {
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
		mThread->create(this, NULL);
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

void	NetworkManager::operator()(void *) {
	while (mSockets.size() > 0) {
		initFds();

		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		if (select(mMaxFd + 1, &mReadFds, &mWriteFds, NULL, &tv) == -1)
			throw SocketException("fail select()");

		checkFdsReadable();
		checkFdsWritable();
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

void	NetworkManager::checkFdsReadable(void) {
	std::list<std::pair<int, NetworkManager::OnSocketEvent *>> sockets;
	{
		ScopedLock scopedLock(mMutex);
		sockets = mSockets;
	}

	for (const auto &socket : sockets)
		if (socket.second && FD_ISSET(socket.first, &mReadFds))
			socket.second->onSocketReadable(socket.first);
}

void	NetworkManager::checkFdsWritable(void) {
	std::list<std::pair<int, NetworkManager::OnSocketEvent *>> sockets;
	{
		ScopedLock scopedLock(mMutex);
		sockets = mSockets;
	}

	for (const auto &socket : sockets)
		if (socket.second && FD_ISSET(socket.first, &mWriteFds))
			socket.second->onSocketWritable(socket.first);
}

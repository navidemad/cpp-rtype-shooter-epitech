#include "NetworkManager.hpp"
#include "SocketException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include <algorithm>

NetworkManager::NetworkManager(void) : mMaxFd(-1), mMutex(PortabilityBuilder::getMutex()), mThreadPool(ThreadPool::getInstance()) {
}

NetworkManager::~NetworkManager(void) {
	mThreadPool->stop();
}

std::list<NetworkManager::Socket>::iterator NetworkManager::findSocket(int socketFd) {
    auto& sockets = getSockets();
    auto& it = sockets.begin();
    while (it != sockets.end())
    {
        if ((*it).fd == socketFd)
            return it;
        ++it;
    }
    return it;
}

void	NetworkManager::addSocket(int socketFd, NetworkManager::OnSocketEvent *listener) {
	if (socketFd == -1)
		throw SocketException("Invalid socket cannot be under the NetworkManager control");

	if (findSocket(socketFd) != getSockets().end())
		throw SocketException("Socket already under NetworkManager control");

    addSocketInList(Socket(socketFd, listener));

	if (socketFd > getMaxFd())
		setMaxFd(socketFd);

	if (getSockets().size() == 1)
		*(getThreadPool()) << std::bind(&NetworkManager::doSelect, this);
}

void	NetworkManager::removeSocket(int socketFd) {
    auto& it_socket = findSocket(socketFd);

    if (it_socket == getSockets().end())
		return;

    eraseSocketInList(it_socket);

	if (socketFd == getMaxFd())
		refreshMaxFd();
}

void 	NetworkManager::refreshMaxFd(void) {
    setMaxFd(-1);

    auto& sockets = getSockets();
	for (const auto &socket : sockets)
		if (socket.fd > getMaxFd())
			setMaxFd(socket.fd);
}

std::shared_ptr<NetworkManager> NetworkManager::getInstance(void) {
    static std::shared_ptr<NetworkManager> instance(new NetworkManager);

	return instance;
}

void	NetworkManager::doSelect(void) {
	while (getSockets().size() > 0) {
		initFds();

		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 10000;
		if (select(getMaxFd() + 1, &(getReadFds()), &(getWriteFds()), NULL, &tv) > 0)
			checkFds();
	}
}

void	NetworkManager::initFds(void) {
	FD_ZERO(&(getReadFds()));
	FD_ZERO(&(getWriteFds()));

    auto& sockets = getSockets();
	for (const auto &socket : sockets) {
		FD_SET(socket.fd, &(getReadFds()));
		FD_SET(socket.fd, &(getWriteFds()));
	}
}

void	NetworkManager::checkFds(void) {
    auto& sockets = getSockets();
    for (auto &socket : sockets) {
		bool readable = FD_ISSET(socket.fd, &(getReadFds())) != 0;
		bool writable = FD_ISSET(socket.fd, &(getWriteFds())) != 0;

		if ((readable || writable) && !socket.isCallbackRunning && socket.listener) {
			socket.isCallbackRunning = true;
			*(getThreadPool()) << std::bind(&NetworkManager::socketCallback, this, socket.fd, readable, writable);
		}
	}
}

void	NetworkManager::socketCallback(int socketFd, bool readable, bool writable) {
    auto& it_socket = findSocket(socketFd);

    if (readable && stillUnderControl(socketFd) && (*it_socket).listener)
        (*it_socket).listener->onSocketReadable((*it_socket).fd);

    if (writable && stillUnderControl(socketFd) && (*it_socket).listener)
        (*it_socket).listener->onSocketWritable((*it_socket).fd);

	if (stillUnderControl(socketFd))
        (*it_socket).isCallbackRunning = false;
}

bool NetworkManager::stillUnderControl(int socketFd) {
	return findSocket(socketFd) != getSockets().end();
}

/*
-------------------  scoped functions --------------------------
*/

void NetworkManager::addSocketInList(const Socket& socket) {
    Scopedlock(mMutex);

    mSockets.push_back(socket);
}

void NetworkManager::eraseSocketInList(std::list<NetworkManager::Socket>::iterator& it) {
    Scopedlock(mMutex);

    mSockets.erase(it);
}

int NetworkManager::getMaxFd(void) const {
    Scopedlock(mMutex);

    return mMaxFd;
}

void NetworkManager::setMaxFd(int fd) {
    Scopedlock(mMutex);

    mMaxFd = fd;
}

fd_set& NetworkManager::getReadFds(void) {
    Scopedlock(mMutex);

    return mReadFds;
}

void NetworkManager::setReadFds(const fd_set& readFds) {
    Scopedlock(mMutex);

    mReadFds = readFds;
}

fd_set& NetworkManager::getWriteFds(void) {
    Scopedlock(mMutex);

    return mWriteFds;
}

void NetworkManager::setWriteFds(const fd_set& writeFds) {
    Scopedlock(mMutex);

    mWriteFds = writeFds;
}

std::shared_ptr<ThreadPool>& NetworkManager::getThreadPool(void) {
    Scopedlock(mMutex);

    return mThreadPool;
}

std::list<NetworkManager::Socket>& NetworkManager::getSockets(void) {
    Scopedlock(mMutex);

    return mSockets;
}

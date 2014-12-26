#include "NetworkManager.hpp"
#include "SocketException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include "Utils.hpp"
#include <algorithm>

std::shared_ptr<NetworkManager> NetworkManager::mInstance = nullptr;

NetworkManager::NetworkManager(void) : mMaxFd(-1), mMutex(PortabilityBuilder::getMutex()), mThreadPool(ThreadPool::getInstance()) {
}

NetworkManager::~NetworkManager(void) {
}

std::list<NetworkManager::Socket>::iterator NetworkManager::findSocket(int socketFd) {
    return std::find_if(mSockets.begin(), mSockets.end(), [&](const NetworkManager::Socket &socket) { return socket.fd == socketFd; });
}

std::list<NetworkManager::Socket>::const_iterator NetworkManager::findSocket(int socketFd) const {
    return std::find_if(mSockets.begin(), mSockets.end(), [&](const NetworkManager::Socket &socket) { return socket.fd == socketFd; });
}

void	NetworkManager::addSocket(int socketFd, NetworkManager::OnSocketEvent *listener) {
    ScopedLock scopedlock(mMutex);;

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
    ScopedLock scopedlock(mMutex);;

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

const std::shared_ptr<NetworkManager> &NetworkManager::getInstance(void) {
    if (mInstance == nullptr)
        mInstance = std::shared_ptr<NetworkManager>(new NetworkManager);

    return mInstance;
}

void	NetworkManager::doSelect(void) {
  while (!Utils::interruptedSignal && mSockets.size() > 0) {
        initFds();

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 500;
        if (select(mMaxFd + 1, &mReadFds, &mWriteFds, NULL, &tv) > 0)
            checkFds();
    }
}

void	NetworkManager::initFds(void) {
    ScopedLock scopedlock(mMutex);;

    FD_ZERO(&mReadFds);
    FD_ZERO(&mWriteFds);

    for (const auto &socket : mSockets) {
        FD_SET(socket.fd, &mReadFds);
        FD_SET(socket.fd, &mWriteFds);
    }
}

void	NetworkManager::checkFds(void) {
    ScopedLock scopedlock(mMutex);;

    for (auto &socket : mSockets) {
        bool readable = FD_ISSET(socket.fd, &mReadFds) != 0;
        bool writable = FD_ISSET(socket.fd, &mWriteFds) != 0;

        if ((readable || writable) && !socket.isCallbackRunning && socket.listener) {
            socket.isCallbackRunning = true;
            *mThreadPool << std::bind(&NetworkManager::socketCallback, this, socket.fd, readable, writable);
        }
    }
}

void	NetworkManager::readCallBack(int socketFd) const {
	std::list<NetworkManager::Socket>::const_iterator socket;
	{
		ScopedLock scopedlock(mMutex);;

		socket = findSocket(socketFd);
		if (socket == mSockets.end())
			return;
	}

	socket->listener->onSocketReadable(socket->fd);
}

void	NetworkManager::writeCallBack(int socketFd) const {
	std::list<NetworkManager::Socket>::const_iterator socket;
	{
		ScopedLock scopedlock(mMutex);;

		socket = findSocket(socketFd);
		if (socket == mSockets.end())
			return;
	}

	socket->listener->onSocketWritable(socket->fd);
}

void	NetworkManager::endCallBack(int socketFd) {
	ScopedLock scopedlock(mMutex);;

	std::list<NetworkManager::Socket>::iterator socket = findSocket(socketFd);
	if (socket != mSockets.end())
		socket->isCallbackRunning = false;
}

void	NetworkManager::socketCallback(int socketFd, bool readable, bool writable) {
	if (readable)
		readCallBack(socketFd);

	if (writable)
		writeCallBack(socketFd);

	endCallBack(socketFd);
}

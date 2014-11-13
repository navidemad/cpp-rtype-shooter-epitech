#include "NetworkManager.hpp"
#include "SocketException.hpp"
#include <algorithm>

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
}

void	NetworkManager::removeSocket(int socketFd) {
	auto socket = findSocket(socketFd);

	if (socket == mSockets.end())
		throw SocketException("Cannot remove a socket which is not under the NetworkManager control");

	mSockets.erase(socket);
}

std::shared_ptr<NetworkManager> NetworkManager::getInstance(void) {
	if (mInstance.get() != nullptr)
		return mInstance;

	return std::shared_ptr<NetworkManager>(new NetworkManager);
}

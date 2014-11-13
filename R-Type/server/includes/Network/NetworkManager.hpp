#pragma once

#include <list>
#include <utility>
#include <memory>

class NetworkManager {

	// CallBack Interface
	public:
		class OnSocketEvent {
			public:
				virtual	~OnSocketEvent(void) {}
				virtual	void	onBytesWritten(int socketFd, unsigned int nbBytes) = 0;
				virtual void	onSocketReadable(int socketFd) = 0;
				virtual void	onSocketClosed(int socketFd) = 0;
		};

	// ctor - dtor
	private:
		NetworkManager(void);
	public:
		~NetworkManager(void);

	// copy / move operators
	public:
		NetworkManager(const NetworkManager &) = delete;
		NetworkManager(const NetworkManager &&) = delete;
		const NetworkManager &operator=(const NetworkManager &) = delete;
		const NetworkManager &operator=(const NetworkManager &&) = delete;


	// singleton handle instance
	public:
		static std::shared_ptr<NetworkManager> getInstance(void);
	private:
		static std::shared_ptr<NetworkManager> mInstance;

	// handle sockets
	public:
		void	addSocket(int socketFd, NetworkManager::OnSocketEvent *listener);
		void	removeSocket(int socketFd);

	// find socket
	private:
		std::list<std::pair<int, NetworkManager::OnSocketEvent *>>::iterator findSocket(int socketFd);
	
	// attributes
	private:
		int mMaxFd;
		std::list<std::pair<int, NetworkManager::OnSocketEvent *>> mSockets;

};

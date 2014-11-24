#pragma once

#include "Config.hpp"
#include "ThreadPool.hpp"
#include "IMutex.hpp"

#include <list>
#include <memory>

class NetworkManager {

	// CallBack Interface
	public:
		class OnSocketEvent {
			public:
				virtual	~OnSocketEvent(void) {}
				virtual void	onSocketReadable(int socketFd) = 0;
				virtual	void	onSocketWritable(int socketFd) = 0;
		};

	// socket struct
	private:
		struct Socket {
			Socket(int pFd = -1, NetworkManager::OnSocketEvent *pListener = nullptr, bool pIsCurrentlyNotifyRead = false, bool pIsCurrentlyNotifyWrite = false)
				: fd(pFd), listener(pListener), isCurrentlyNotifyRead(pIsCurrentlyNotifyRead), isCurrentlyNotifyWrite(pIsCurrentlyNotifyWrite) {}

			int fd;
			NetworkManager::OnSocketEvent *listener;
			bool isCurrentlyNotifyRead;
			bool isCurrentlyNotifyWrite;
		};

	// ctor - dtor
	private:
		explicit NetworkManager(void);
	public:
		~NetworkManager(void);

	// copy / move operators
	public:
		NetworkManager(const NetworkManager &) = delete;
		NetworkManager(NetworkManager &&) = delete;
		const NetworkManager &operator=(const NetworkManager &) = delete;
		const NetworkManager &operator=(NetworkManager &&) = delete;


	// singleton handle instance
	public:
		static std::shared_ptr<NetworkManager> getInstance(void);

	// handle sockets
	public:
		void	addSocket(int socketFd, NetworkManager::OnSocketEvent *listener);
		void	removeSocket(int socketFd);

	// internal tools
	private:
		std::list<NetworkManager::Socket>::iterator findSocket(int socketFd);
		void	refreshMaxFd(void);
		void	doSelect(void);
		void	initFds(void);
		void	checkFds(void);
		void	onSocketReadable(int socketFd);
		void	onSocketWritable(int socketFd);

	// attributes
	private:
		int mMaxFd;
		fd_set mReadFds;
		fd_set mWriteFds;
		std::shared_ptr<IMutex> mMutex;
		std::shared_ptr<ThreadPool> mThreadPool;
		std::list<NetworkManager::Socket> mSockets;

};

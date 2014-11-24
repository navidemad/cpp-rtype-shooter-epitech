#pragma once

#include "Config.hpp"
#include "IThread.hpp"
#include "IMutex.hpp"

#include <list>
#include <utility>
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
		std::list<std::pair<int, NetworkManager::OnSocketEvent *>>::iterator findSocket(int socketFd);
		void  refreshMaxFd(void);
	public:
		void	operator()(void *);
	private:
		void	initFds(void);
		void	checkFdsReadable(void);
		void	checkFdsWritable(void);

	// attributes
	private:
		int mMaxFd;
		fd_set mReadFds;
		fd_set mWriteFds;
		std::shared_ptr<IMutex> mMutex;
		std::shared_ptr<IThread<NetworkManager *, void *>> mThread;
		std::list<std::pair<int, NetworkManager::OnSocketEvent *>> mSockets;

};

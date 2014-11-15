#pragma once

#include <list>
#include <utility>
#include <memory>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "IMutex.hpp"

class NetworkManager {

	// CallBack Interface
	public:
		class OnSocketEvent {
			public:
				virtual	~OnSocketEvent(void) {}
				virtual void	onSocketReadable(int socketFd) = 0;
				virtual	void	onSocketWritable(int socketFd) = 0;
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

	// internal tools
	private:
		std::list<std::pair<int, NetworkManager::OnSocketEvent *>>::iterator findSocket(int socketFd);
		void  refreshMaxFd(void);
	public: // A PASSER EN PRIVATE UNE FOIS LABSTRACT THREAD OK
		void	run(void);
	private:
		void	initFds(void);
		void	checkFds(void);
		void	startThread(void);

	// attributes
	private:
		int mMaxFd;
		fd_set mReadFds;
		fd_set mWriteFds;
		std::shared_ptr<IMutex> mMutex;
		std::list<std::pair<int, NetworkManager::OnSocketEvent *>> mSockets;

};

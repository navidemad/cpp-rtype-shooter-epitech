#pragma once

#include <list>
#include <utility>
#include <memory>
#include "IThread.hpp"
#include "IMutex.hpp"

#ifdef __unix__
# include <sys/types.h>
#elif defined(_WIN32) || defined(WIN32)
// # include <Winsock2.h> // provoque des erreurs de compilation, et �a compile sans sur windows
#endif

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
		void	operator()(void *);
	private:
		void	initFds(void);
		void	checkFds(void);

	// attributes
	private:
		int mMaxFd;
		fd_set mReadFds;
		fd_set mWriteFds;
		std::shared_ptr<IMutex> mMutex;
		std::shared_ptr<IThread<NetworkManager *, void *>> mThread;
		std::list<std::pair<int, NetworkManager::OnSocketEvent *>> mSockets;

};

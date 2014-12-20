#pragma once

#include "Config.hpp"
#include "ThreadPool.hpp"
#include "IMutex.hpp"
#include "NoCopyable.hpp"

#include <list>
#include <memory>

class NetworkManager : public NoCopyable {

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
			Socket(int pFd = -1, NetworkManager::OnSocketEvent *pListener = nullptr, bool pIsCallbackRunning = false)
				: fd(pFd), listener(pListener), isCallbackRunning(pIsCallbackRunning) {}

			int fd;
			NetworkManager::OnSocketEvent *listener;
			bool isCallbackRunning;
		};

	// ctor - dtor
	private:
		NetworkManager(void);
        static std::weak_ptr<NetworkManager> mInstance;
	public:
		~NetworkManager(void);

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
		void	socketCallback(int socketFd, bool readable, bool writable);
		bool	stillUnderControl(int socketFd);

    // scoped functions
    private:
        void addSocketInList(const Socket& socket);
        void eraseSocketInList(std::list<NetworkManager::Socket>::iterator& it);

        int getMaxFd(void) const;
        void setMaxFd(int fd);

        fd_set& getReadFds(void);
        void setReadFds(const fd_set& readFds);

        fd_set& getWriteFds(void);
        void setWriteFds(const fd_set& writeFds);

        std::shared_ptr<ThreadPool>& getThreadPool(void);

        std::list<NetworkManager::Socket>& getSockets(void);

	// attributes
	private:
		int mMaxFd;
		fd_set mReadFds;
		fd_set mWriteFds;
		std::shared_ptr<IMutex> mMutex;
		std::shared_ptr<ThreadPool> mThreadPool;
		std::list<NetworkManager::Socket> mSockets;

};

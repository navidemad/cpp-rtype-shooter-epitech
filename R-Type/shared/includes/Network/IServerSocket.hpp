#pragma once

#include "IClientSocket.hpp"

#include <memory>

class IServerSocket {

	// CallBack interface
	public:
		class OnSocketEvent {
			public:
                virtual	~OnSocketEvent() = default;
				virtual void	onNewConnection(IServerSocket *socket) = 0;
		};

	// virtual destructor
	public:
        virtual ~IServerSocket(void) = default;

	// init
	public:
		virtual void	createServer(int port, int queueSize) = 0;
		virtual void	closeServer(void) = 0;

	// listeners
	public:
		virtual void	setOnSocketEventListener(IServerSocket::OnSocketEvent *listener) = 0;

	// handle clients
	public:
		virtual std::shared_ptr<IClientSocket>	getNewClient(void) = 0;
		
};

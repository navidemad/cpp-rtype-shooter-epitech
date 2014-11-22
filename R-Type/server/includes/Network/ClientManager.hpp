#pragma once

#include <list>
#include <memory>
#include "Client.hpp"
#include "IServerSocket.hpp"

class ClientManager : public IServerSocket::OnSocketEvent {

	// ctor / dtor
	public:
        explicit ClientManager(void);
		~ClientManager(void);

	// copy / move operators
	public:
		ClientManager(const ClientManager &) = delete;
		ClientManager(ClientManager &&) = delete;
		const ClientManager &operator=(const ClientManager &) = delete;
		const ClientManager &operator=(ClientManager &&) = delete;

	// interface implementation
	public:
		void	onNewConnection(IServerSocket *socket);

	// attributes
	private:
		std::list<Client> mClients;
		std::shared_ptr<IServerSocket> mServer;

};

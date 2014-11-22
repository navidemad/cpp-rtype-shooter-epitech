#pragma once

#include <list>
#include <memory>
#include "Client.hpp"
#include "IServerSocket.hpp"

class ClientManager : public IServerSocket::OnSocketEvent, public Client::OnClientEvent {

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

	// handle client manager
	public:
		void	run(void);

	// events
	public:
		void	onNewConnection(IServerSocket *socket);
		void	onClientDisconnected(const Client &client);

	// attributes
	private:
		std::list<std::shared_ptr<Client>> mClients;
		std::shared_ptr<IServerSocket> mServer;

		static const int SERVER_TCP_PORT = 4242;
		static const int SERVER_TCP_QUEUE = 1024;

};

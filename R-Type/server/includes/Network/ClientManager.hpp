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
		void	onClientCreateGame(const Client &client, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers);
		void	onClientJoinGame(const Client &client, const std::string &name);
		void	onClientShowGame(const Client &client, const std::string &name);
		void	onClientDeleteGame(const Client &client, const std::string &name);
		void	onClientListGames(const Client &client);
		void	onClientListLevels(const Client &client);
		void	onClientDisconnect(const Client &client);
		void	onClientHandshake(const Client &client);
		void	onClientObserverGame(const Client &client, const std::string &name);
		void	onClientLeaveGame(const Client &client, const std::string &name);
		void	onClientUpdatePseudo(const Client &client, const std::string &pseudo);

	// attributes
	private:
		std::list<std::shared_ptr<Client>> mClients;
		std::shared_ptr<IServerSocket> mServer;

		static const int SERVER_TCP_PORT = 4242;
		static const int SERVER_TCP_QUEUE = 1024;

};

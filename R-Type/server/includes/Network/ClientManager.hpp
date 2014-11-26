#pragma once

#include <list>
#include <memory>
#include "ErrorStatus.hpp"
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
		class OnClientManagerEvent {
			public:
				virtual ~OnClientManagerEvent(void) {}
				virtual void onClientDisconnected(const std::string &host) = 0;
				virtual void onClientCreateGame(const std::string &host, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers) = 0;
				virtual void onClientJoinGame(const std::string &host, const std::string &name, const std::string &pseudo) = 0;
				virtual void onClientShowGame(const std::string &host, const std::string &name) = 0;
				virtual void onClientDeleteGame(const std::string &host, const std::string &name) = 0;
				virtual void onClientListGames(const std::string &host) = 0;
				virtual void onClientListLevels(const std::string &host) = 0;
				virtual void onClientObserveGame(const std::string &host, const std::string &name) = 0;
				virtual void onClientLeaveGame(const std::string &host) = 0;
				virtual void onClientUpdatePseudo(const std::string &host, const std::string &pseudo) = 0;
		};

		void	onNewConnection(IServerSocket *socket);
		void	onClientDisconnected(const Client &client);
		void	onClientCreateGame(const Client &client, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers);
		void	onClientJoinGame(const Client &client, const std::string &name);
		void	onClientShowGame(const Client &client, const std::string &name);
		void	onClientDeleteGame(const Client &client, const std::string &name);
		void	onClientListGames(const Client &client);
		void	onClientListLevels(const Client &client);
		void	onClientDisconnect(const Client &client);
		void	onClientHandshake(Client &client);
		void	onClientObserveGame(const Client &client, const std::string &name);
		void	onClientLeaveGame(const Client &client);
		void	onClientUpdatePseudo(Client &client, const std::string &pseudo);

		void	setListener(ClientManager::OnClientManagerEvent *listener);

	// intern methods
	private:
		std::list<std::shared_ptr<Client>>::iterator findClient(const std::string &host);

	// send commands
	public:
		void	sendError(const std::list<std::string> &hosts, const ErrorStatus &errorStatus);
		void	sendShowGame(const std::list<std::string> &hosts, const std::string &name, const std::string &levelName, int nbPlayers, int maxPlayers, int nbObservers, int maxObservers);
		void	sendEndGame(const std::list<std::string> &hosts);
		void	sendShowLevel(const std::list<std::string> &hosts, const std::string &name, const std::string &script);

	// attributes
	private:
		ClientManager::OnClientManagerEvent *mListener;
		std::list<std::shared_ptr<Client>> mClients;
		std::shared_ptr<IServerSocket> mServer;

		static const int SERVER_TCP_PORT = 4242;
		static const int SERVER_TCP_QUEUE = 1024;

};

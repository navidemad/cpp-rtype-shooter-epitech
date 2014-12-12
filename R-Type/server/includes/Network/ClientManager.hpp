#pragma once

#include "Peer.hpp"
#include "ErrorStatus.hpp"
#include "Client.hpp"
#include "IServerSocket.hpp"
#include "NoCopyable.hpp"

#include <list>
#include <memory>

class ClientManager : public NoCopyable, public IServerSocket::OnSocketEvent, public Client::OnClientEvent {

	// ctor / dtor
	public:
        ClientManager(void);
		~ClientManager(void);

	// handle client manager
	public:
		void	run(void);

	// events
	public:
		class OnClientManagerEvent {
			public:
				virtual ~OnClientManagerEvent(void) {}
				virtual void onClientDisconnected(const Peer &peer) = 0;
				virtual void onClientCreateGame(const Peer &peer, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers) = 0;
				virtual void onClientJoinGame(const Peer &peer, const std::string &name, const std::string &pseudo) = 0;
				virtual void onClientShowGame(const Peer &peer, const std::string &name) = 0;
				virtual void onClientDeleteGame(const Peer &peer, const std::string &name) = 0;
				virtual void onClientListGames(const Peer &peer) = 0;
				virtual void onClientListLevels(const Peer &peer) = 0;
				virtual void onClientObserveGame(const Peer &peer, const std::string &name) = 0;
				virtual void onClientLeaveGame(const Peer &peer) = 0;
				virtual void onClientUpdatePseudo(const Peer &peer, const std::string &pseudo) = 0;
		};

		void	onNewConnection(IServerSocket *socket);
		void	onClientDisconnected(const Client &client);
		void	onClientCreateGame(const Client &client, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers);
		void	onClientJoinGame(const Client &client, const std::string &name);
		void	onClientShowGame(const Client &client, const std::string &name);
		void	onClientDeleteGame(const Client &client, const std::string &name);
		void	onClientListGames(const Client &client);
		void	onClientListLevels(const Client &client);
		void	onClientHandshake(Client &client, int udpPort);
		void	onClientObserveGame(const Client &client, const std::string &name);
		void	onClientLeaveGame(const Client &client);
		void	onClientUpdatePseudo(Client &client, const std::string &pseudo);

		void	setListener(ClientManager::OnClientManagerEvent *listener);

	// intern methods
	private:
		std::list<std::shared_ptr<Client>>::iterator findClient(const Peer &peer);
		void logInfo(const Peer &peer, const std::string &log);

	// send commands
	public:
		void	sendError(const std::list<Peer> &peers, const ErrorStatus &errorStatus);
		void	sendShowGame(const std::list<Peer> &peers, const std::string &name, const std::string &levelName, int nbPlayers, int maxPlayers, int nbObservers, int maxObservers);
		void	sendEndGame(const std::list<Peer> &peers);
		void	sendShowLevel(const std::list<Peer> &peers, const std::string &name, const std::string &script);

	// attributes
	private:
		ClientManager::OnClientManagerEvent *mListener;
		std::list<std::shared_ptr<Client>> mClients;
		std::shared_ptr<IServerSocket> mServer;

	public:
		static const int SERVER_TCP_PORT = 4245;
		static const int SERVER_TCP_QUEUE = 1024;

};

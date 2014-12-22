#pragma once

#include "Peer.hpp"
#include "ClientManager.hpp"
#include "GamesManager.hpp"
#include "NoCopyable.hpp"

class RTypeServer : public NoCopyable, public ClientManager::OnClientManagerEvent, public GamesManager::OnGamesManagerEvent {

    // ctor / dtor
    public:
        RTypeServer(void);
        ~RTypeServer(void) = default;

    // exec function
    public:
        int run(void);

	// events
	public:
		void onClientDisconnected(const Peer &peer);
		void onClientCreateGame(const Peer &peer, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers);
		void onClientJoinGame(const Peer &peer, const std::string &name, const std::string &pseudo);
		void onClientShowGame(const Peer &peer, const std::string &name);
		void onClientDeleteGame(const Peer &peer, const std::string &name);
		void onClientListGames(const Peer &peer);
		void onClientListLevels(const Peer &peer);
		void onClientObserveGame(const Peer &peer, const std::string &name);
		void onClientLeaveGame(const Peer &peer);
		void onClientUpdatePseudo(const Peer &peer, const std::string &pseudo);
		void onEndGame(const std::string &gameName, const std::list<Peer> &gameUsers);

	// internal methods
	private:
		void startInfo(void) const;

	// attributes
	private:
		ClientManager mClientManager;
		GamesManager mGamesManager;

};

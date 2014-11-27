#pragma once

#include "ClientManager.hpp"
#include "GamesManager.hpp"
#include "NoCopyable.hpp"

class RTypeServer : public NoCopyable, public ClientManager::OnClientManagerEvent {

    // ctor / dtor
    public:
        explicit RTypeServer(void);
        ~RTypeServer(void) = default;

    // exec function
    public:
        void run(void);

	// events
	public:
		void onClientDisconnected(const std::string &host);
		void onClientCreateGame(const std::string &host, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers);
		void onClientJoinGame(const std::string &host, const std::string &name, const std::string &pseudo);
		void onClientShowGame(const std::string &host, const std::string &name);
		void onClientDeleteGame(const std::string &host, const std::string &name);
		void onClientListGames(const std::string &host);
		void onClientListLevels(const std::string &host);
		void onClientObserveGame(const std::string &host, const std::string &name);
		void onClientLeaveGame(const std::string &host);
		void onClientUpdatePseudo(const std::string &host, const std::string &pseudo);

    // attributes
    private:
        ClientManager mClientManager;
        GamesManager mGamesManager;
};
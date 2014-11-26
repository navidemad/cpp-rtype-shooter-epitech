#pragma once

#include "ClientManager.hpp"
#include "GamesManager.hpp"

class RTypeServer : public ClientManager::OnClientManagerEvent {

    // ctor / dtor
    public:
        explicit RTypeServer(void);
        ~RTypeServer(void);

    // copy / move operators
    public:
        RTypeServer(const RTypeServer &) = delete;
        RTypeServer(const RTypeServer &&) = delete;
        const RTypeServer &operator=(const RTypeServer &) = delete;
        const RTypeServer &operator=(const RTypeServer &&) = delete;

    // exec function
    public:
        int run(void);

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
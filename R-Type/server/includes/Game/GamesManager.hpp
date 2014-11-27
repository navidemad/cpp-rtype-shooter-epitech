#pragma once

#include "Game.hpp"
#include "ThreadPool.hpp"
#include "IMutex.hpp"
#include "Utils.hpp"
#include "ScriptLoader.hpp"
#include "PlayerCommunicationManager.hpp"

#include <string>
#include <memory>
#include <vector>

class GamesManager : public PlayerCommunicationManager::OnPlayerCommunicationManagerEvent, public Game::OnGameEvent {

    // ctor / dtor
    public:
        explicit GamesManager(void);
        ~GamesManager(void);

    // copy / move operators
    public:
        GamesManager(const GamesManager &) = delete;
        GamesManager(const GamesManager &&) = delete;
        const GamesManager &operator=(const GamesManager &) = delete;
        const GamesManager &operator=(const GamesManager &&) = delete;

    // entry point
    public:
        void run(void);

	// player communication manager events
	public:
		void onPlayerFire(const PlayerCommunicationManager &playerCommunicationManager, const std::string &host, int port);
		void onPlayerMove(const PlayerCommunicationManager &playerCommunicationManager, IResource::Direction direction, const std::string &host, int port);

    // game events
    public:
        void onTerminatedGame(std::shared_ptr<Game>);

	// network workflow utils functions
	public:
        void    createGame(const Game::GameProperties&properties, const std::string& host);
        void    removeGame(const std::string&);
        void    disconnectHostFromHisEventualGameRunning(const std::string& host);
		void	joinGame(const std::string &host, const std::string &name, const std::string &pseudo);
		void	observeGame(const std::string &host, const std::string &name);
		void	leaveGame(const std::string &host);
		void	updatePseudo(const std::string &host, const std::string &pseudo);
		const Game::GameProperties &getGameProperties(const std::string &name) const;
		const std::list<Game::GameProperties> &getGamesProperties(void) const;
        std::vector<std::shared_ptr<Game>>::const_iterator findGameByName(const std::string& name) const;
        std::vector<std::shared_ptr<Game>>::const_iterator findGameByUserAddressIp(const std::string& name) const;

    // attributes
    private:
		ScriptLoader mScriptLoader;
		std::shared_ptr<ThreadPool> mThreadPool;
        std::vector<std::shared_ptr<Game>> mGames;
        std::shared_ptr<IMutex> mMutex;
		PlayerCommunicationManager mPlayerCommunicationManager;

};

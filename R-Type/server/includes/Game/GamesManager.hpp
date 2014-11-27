#pragma once

#include "Game.hpp"
#include "ThreadPool.hpp"
#include "IMutex.hpp"
#include "Utils.hpp"
#include "ScriptLoader.hpp"
#include "PlayerCommunicationManager.hpp"
#include "NoCopyable.hpp"

#include <string>
#include <memory>
#include <vector>

class GamesManager : public NoCopyable, public PlayerCommunicationManager::OnPlayerCommunicationManagerEvent, public Game::OnGameEvent {

    // ctor / dtor
    public:
        explicit GamesManager(void);
        ~GamesManager(void);

    // entry point
    public:
        void run(void);

	// player communication manager events
	public:
		void onPlayerFire(const PlayerCommunicationManager &playerCommunicationManager, const std::string &host, int port);
		void onPlayerMove(const PlayerCommunicationManager &playerCommunicationManager, IResource::Direction direction, const std::string &host, int port);

    // game events
    public:
        void onTerminatedGame(const std::shared_ptr<Game>&);

	// network workflow utils functions
	public:
        void    createGame(const Game::GameProperties&properties);
        void    removeGame(const std::string&);
        void    joinGame(Game::USER_TYPE typeUser, const std::string &host, const std::string &name, const std::string &pseudo);
        void    playGame(const std::string &host, const std::string &name, const std::string &pseudo);
        void    spectateGame(const std::string &host, const std::string &name, const std::string &pseudo);
        void	leaveGame(const std::string &host, bool throwExcept = true);
		void	updatePseudo(const std::string &host, const std::string &pseudo);
		const Game::GameProperties &getGameProperties(const std::string &name);
		const std::list<Game::GameProperties> &getGamesProperties(void) const;
        std::vector<std::shared_ptr<Game>>::iterator findGameByGamePtr(const std::shared_ptr<Game>& target);
        std::vector<std::shared_ptr<Game>>::iterator findGameByName(const std::string& name);
        std::vector<std::shared_ptr<Game>>::iterator findGameByHost(const std::string& host);

    // attributes
    private:
		ScriptLoader mScriptLoader;
		std::shared_ptr<ThreadPool> mThreadPool;
        std::vector<std::shared_ptr<Game>> mGames;
        std::shared_ptr<IMutex> mMutex;
		PlayerCommunicationManager mPlayerCommunicationManager;

};

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

class GamesManager : public PlayerCommunicationManager::OnPlayerCommunicationManagerEvent {

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

    // internal functions
    public:
        void run(void);
        void createGame(const Game::GameProperties&, const std::string&);
        std::vector<std::shared_ptr<Game>>::iterator findGame(const std::string& name);
        void removeGame(const std::string&);

	// player communication manager events
	public:
		void onPlayerFire(const PlayerCommunicationManager &playerCommunicationManager, const std::string &host, int port);
		void onPlayerMove(const PlayerCommunicationManager &playerCommunicationManager, IResource::Direction direction, const std::string &host, int port);

    // attributes
    private:
		ScriptLoader mScriptLoader;
		std::shared_ptr<ThreadPool> mThreadPool;
        std::vector<std::shared_ptr<Game>> mGames;
        std::shared_ptr<IMutex> mMutex;
		PlayerCommunicationManager mPlayerCommunicationManager;
	
	static const int THREAD_POOL_SIZE = 6;

};

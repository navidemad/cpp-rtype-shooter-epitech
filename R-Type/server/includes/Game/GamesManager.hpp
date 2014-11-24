#pragma once

#include "Game.hpp"
#include "ThreadPool.hpp"
#include "IMutex.hpp"
#include "Utils.hpp"

#include <string>
#include <memory>
#include <vector>

class GamesManager {

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
        void createGame(const Game::GameProperties&);
        std::vector<std::shared_ptr<Game>>::iterator findGame(const std::string& name);
        void removeGame(const std::string&);

    // attributes
    private:
        std::shared_ptr<ThreadPool> mThreadPool;
        std::vector<std::shared_ptr<Game>> mGames;
        std::shared_ptr<IMutex> mMutex;
	
	static const int THREAD_POOL_SIZE = 6;

};

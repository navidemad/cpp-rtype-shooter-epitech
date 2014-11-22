#pragma once

#include "Game.hpp"
#include "ThreadPool.hpp"
#include "Utils.hpp"

#include <string>
#include <memory>

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
        void removeGame(const std::string&);

    // attributes
    private:
        ThreadPool mThreadPool;
	
	static const int THREAD_POOL_SIZE = 6;

};

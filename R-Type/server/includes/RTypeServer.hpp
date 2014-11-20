#pragma once

#include "ClientManager.hpp"
#include "ScriptLoader.hpp"
#include "GamesManager.hpp"

class RTypeServer {

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

    // attributes
    private:
        ClientManager mClientManager;
        ScriptLoader mScriptLoader;
        GamesManager mGamesManager;
};
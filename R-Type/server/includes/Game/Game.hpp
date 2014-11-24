#pragma once

#include "Timer.hpp"

#include <string>

class Game {

    // game properties
    public:
        class GameProperties {

        // ctor / dtor
        public:
            GameProperties(void);
            ~GameProperties(void);

        // copy / move operators
        public:
            GameProperties(const GameProperties &) = delete;
            GameProperties(const GameProperties &&) = delete;
            const GameProperties &operator=(const GameProperties &) = delete;
            const GameProperties &operator=(const GameProperties &&) = delete;

        // setters
        public:
            void setName(const std::string&);
            void setLevelName(const std::string&);
            void setNbPlayers(int);
            void setNbSpectators(int);

        // getters
        public:
            const std::string& getName(void) const;
            const std::string& getLevelName(void) const;
            int getNbPlayers(void) const;
            int getNbSpectators(void) const;

        // attributes
        private:
            std::string mName;
            std::string mLevelName;
            int mNbPlayers;
            int mNbSpectators;
        };

    // ctor / dtor
    public:
        explicit Game(const Game::GameProperties& properties);
        ~Game(void);

    // copy / move operators
    public:
        Game(const Game &) = delete;
        Game(const Game &&) = delete;
        const Game &operator=(const Game &) = delete;
        const Game &operator=(const Game &&) = delete;

    // internal functions
    public:
        void updateTimer(void);
        void updatePositions(void);
        void checkRessources(void);
        void addPlayer(void);
        void delPlayer(void);
        void terminateGame(void);
        const Game::GameProperties& getProperties(void) const;

    // attributes
    private:
        Timer mTimer;
        const Game::GameProperties& mProperties;

};

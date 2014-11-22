#pragma once

#include "Timer.hpp"

#include <string>

class Game {

    // ctor / dtor
    public:
        explicit Game(void);
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

    // attributes
    private:
        Timer mTimer;

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
                inline void setName(const std::string&);
                inline void setLevelName(const std::string&);
                inline void setNbPlayers(int);
                inline void setNbSpectators(int);

            // getters
            public:
                inline const std::string& getName(void) const;
                inline const std::string& getLevelName(void) const;
                inline int getNbPlayers(void) const;
                inline int getNbSpectators(void) const;

            // attributes
            private:
                std::string mName;
                std::string mLevelName;
                int mNbPlayers;
                int mNbSpectators;
       };
};

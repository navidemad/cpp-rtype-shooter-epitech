#pragma once

#include "Timer.hpp"
#include "Client.hpp"

#include <string>
#include <memory>
#include <list>

class Game : public std::enable_shared_from_this<Game> {

    // game properties
    public:
        class GameProperties {

        // ctor / dtor
        public:
            GameProperties(void);
            ~GameProperties(void) = default;

        // setters
        public:
            void setName(const std::string&);
            void setLevelName(const std::string&);
            void setNbPlayers(int);
            void setNbMaxPlayers(int);
            void setNbSpectators(int);
            void setNbMaxSpectators(int);

        // getters
        public:
            const std::string& getName(void) const;
            const std::string& getLevelName(void) const;
            int getNbPlayers(void) const;
			int getMaxPlayers(void) const;
            int getNbSpectators(void) const;
			int getMaxSpectators(void) const;

        // attributes
        private:
            std::string mName;
            std::string mLevelName;
            int mNbPlayers;
            int mNbMaxPlayers;
            int mNbSpectators;
            int mNbMaxSpectators;
        };

    // ctor / dtor
    public:
        explicit Game(const Game::GameProperties& properties, const std::string& hostOwner);
        ~Game(void) = default;

    // copy / move operators
    public:
        Game(const Game &) = delete;
        Game(const Game &&) = delete;
        const Game &operator=(const Game &) = delete;
        const Game &operator=(const Game &&) = delete;

    // type user
    public:
        enum class USER_TYPE { PLAYER, SPECTATOR };

    // events
    public:
        class OnGameEvent {
        public:
            virtual ~OnGameEvent(void) {}
            virtual void onTerminatedGame(std::shared_ptr<Game>) = 0;
        };
        void	setListener(Game::OnGameEvent *listener);

    // internal functions
    public:
        void updatePositions(void);
        void checkRessources(void);
        int countUserByType(Game::USER_TYPE type) const;
        void tryAddPlayer(Game::USER_TYPE type, const std::string& ipAddress);
        void tryAddSpectator(Game::USER_TYPE type, const std::string& ipAddress);
        void addUser(Game::USER_TYPE type, const std::string& ipAddress);
        void delUser(const std::string& ipAddress);
        std::list<std::pair<Game::USER_TYPE, std::string>>::const_iterator findUserByAddressIp(const std::string& name) const;
        const std::list<std::pair<Game::USER_TYPE, std::string>>& getUsers() const;
        void terminateGame(void);
        const Game::GameProperties& getProperties(void) const;

    // attributes
    private:
        Game::OnGameEvent *mListener;
        Timer mTimer;
        Game::GameProperties mProperties;
        std::list<std::pair<Game::USER_TYPE, std::string>> mUsers;

};

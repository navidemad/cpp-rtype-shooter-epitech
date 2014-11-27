#pragma once

#include "Timer.hpp"
#include "Client.hpp"
#include "NoCopyable.hpp"

#include <string>
#include <memory>
#include <list>

class Game : public NoCopyable, public std::enable_shared_from_this<Game>  {

    /*
    ** ********************************************************************************
    **                       [Nested Class] GameProperties
    ** ********************************************************************************
    */
    public:
        class GameProperties {

        // ctor / dtor
        public:
            GameProperties(void) : mName(""), mLevelName(""), mNbPlayers(0), mNbMaxPlayers(0), mNbSpectators(0), mNbMaxSpectators(0) { }
            ~GameProperties(void) = default;

        // setters
        public:
            void setName(const std::string& name) { mName = name; }
            void setLevelName(const std::string& levelName) { mLevelName = levelName; }
            void setNbPlayers(int nbPlayers) { mNbPlayers = nbPlayers; }
            void setNbMaxPlayers(int nbPlayers) { mNbMaxPlayers = nbPlayers; }
            void setNbSpectators(int nbSpectators) { mNbSpectators = nbSpectators; }
            void setNbMaxSpectators(int nbSpectators) { mNbMaxSpectators = nbSpectators; }

        // getters
        public:
            const std::string& getName(void) const { return mName; }
            const std::string& getLevelName(void) const { return mLevelName; }
            int getNbPlayers(void) const { return mNbPlayers; }
            int getMaxPlayers(void) const { return mNbMaxPlayers; }
            int getNbSpectators(void) const { return mNbSpectators; }
            int getMaxSpectators(void) const { return mNbMaxSpectators; }

        // attributes
        private:
            std::string mName;
            std::string mLevelName;
            int mNbPlayers;
            int mNbMaxPlayers;
            int mNbSpectators;
            int mNbMaxSpectators;
        };

    // type user
    public:
        enum class USER_TYPE { PLAYER, SPECTATOR };

    /*
    ** ********************************************************************************
    **                            [Nested Class] User
    ** ********************************************************************************
    */
    public:
        class User {

            // ctor / dtor
            public:
                explicit User(void) { }
                ~User(void) = default;

            // setters
            public:
                void setHost(const std::string& host) { mHost = host; }
                void setPseudo(const std::string& pseudo) { mPseudo = pseudo; }
                void setType(Game::USER_TYPE type) { mType = type; }

            // getters
            public:
                const std::string& getHost(void) const { return mHost; }
                const std::string& getPseudo(void) const { return mPseudo; }
                Game::USER_TYPE getType(void) const { return mType; }

            // attributes
            private:
                std::string mHost;
                std::string mPseudo;
                Game::USER_TYPE mType;

        };

    /*
    ** ********************************************************************************
    **                            [Nested Class] Component
    ** ********************************************************************************
    */
    public:
        class Component {

            // ctor / dtor
            public:
                explicit Component(void) { }
                ~Component(void) = default;

            // setters
            public:
                void setX(float x) { mX = x; }
                void setY(float y) { mY = y; }
                void setAngle(float angle) { mAngle = angle; }
                void setLife(int life) { mLife = life; }

            // getters
            public:
                float getX(void) const { return mX; }
                float getY(void) const { return mY; }
                float getAngle(void) const { return mAngle; }
                int getLife(void) const { return mLife; }

            // attributes
            private:
                float mX;
                float mY;
                float mAngle;
                int mLife;

        };

    /*
    ** ********************************************************************************
    **                            [Class] Game
    ** ********************************************************************************
    */

    // ctor / dtor
    public:
        explicit Game(const Game::GameProperties& properties);
        ~Game(void) = default;

    // events
    public:
        class OnGameEvent {
        public:
            virtual ~OnGameEvent(void) {}
            virtual void onTerminatedGame(const std::shared_ptr<Game>&) = 0;
        };
        void	setListener(Game::OnGameEvent *listener);

    // threadpool running functions
    public:
        void checkStateGame(void);
        void killComponentOutOfScreen(void);
        void updatePositions(void);
        void checkRessources(void);

    // internal functions
    public:
        int countUserByType(Game::USER_TYPE type) const;
        std::list<Game::User>::iterator findUserByHost(const std::string& host);
        void tryAddPlayer(const User& user);
        void tryAddSpectator(const User& user);
        void addUser(Game::USER_TYPE type, const std::string& ipAddress, const std::string& pseudo);
        void delUser(const std::string& ipAddress);
        const std::list<Game::User>& getUsers() const;
        void terminateGame(void);
        const Game::GameProperties& getProperties(void) const;

    // attributes
    private:
        Game::OnGameEvent *mListener;
        Timer mTimer;
        Game::GameProperties mProperties;
        std::list<Game::User> mUsers;
        std::list<Game::Component> mComponents;
        bool mIsRunning;
        bool mAlreadyRunOneTime;

};

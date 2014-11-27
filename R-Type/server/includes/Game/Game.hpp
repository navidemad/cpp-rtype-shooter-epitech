#pragma once

#include "IMutex.hpp"
#include "Timer.hpp"
#include "Client.hpp"
#include "NoCopyable.hpp"
#include "IResource.hpp"

#include <string>
#include <memory>
#include <list>
#include <functional>

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
                void setId(uint64_t id) { mUserId = id; }

            // getters
            public:
                const std::string& getHost(void) const { return mHost; }
                const std::string& getPseudo(void) const { return mPseudo; }
                Game::USER_TYPE getType(void) const { return mType; }
                uint64_t getId(void) const { return mUserId; }

            // attributes
            private:
                std::string mHost;
                std::string mPseudo;
                Game::USER_TYPE mType;
                uint64_t mUserId;

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
                explicit Component(int userId = -1) : mUserId(userId) { }
                ~Component(void) = default;

            // setters
            public:
                void setX(float x) { mX = x; }
                void setY(float y) { mY = y; }
                void setWidth(int width) { mWidth = width; }
                void setHeight(int height) { mHeight = height; }
                void setAngle(float angle) { mAngle = angle; }
                void setSpeed(float speed) { mSpeed = speed; }
                void setLife(int life) { mLife = life; }
                void setType(IResource::Type type) { mType = type; }
                void setId(uint64_t id) { mUserId = id; }

            // getters
            public:
                float getX(void) const { return mX; }
                float getY(void) const { return mY; }
                int getWidth(void) const { return mWidth; }
                int getHeight(void) const { return mHeight; }
                float getAngle(void) const { return mAngle; }
                float getSpeed(void) const { return mSpeed; }
                int getLife(void) const { return mLife; }
                IResource::Type getType(void) { return mType; }
                uint64_t getId(void) const { return mUserId; }

            // attributes
            private:
                float mX;
                float mY;
                int mWidth;
                int mHeight;
                float mAngle;
                float mSpeed;
                int mLife;
                IResource::Type mType;
                uint64_t mUserId;
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

    // referentiel
    public:
        static const float XMAX;
        static const float YMAX;

    // threadpool running functions
    public:
        void stateGame(void);
        void check(void);
        void update(void);

    // ressources workflow functions
    public:
        bool outOfScreen(const Component& component);
        bool collisionTouch(const Component& component, const Component& obstacle) const;
        bool collision(const Component& component);

    // internal functions
    public:
        int countUserByType(Game::USER_TYPE type) const;
        std::vector<Game::User>::iterator findUserByHost(const std::string& host);
        std::vector<Game::User>::iterator findUserById(uint64_t id);
        void tryAddPlayer(const User& user);
        void tryAddSpectator(const User& user);
        void addUser(Game::USER_TYPE type, const std::string& ipAddress, const std::string& pseudo);
        void delUser(const std::string& ipAddress);
        void transferPlayerToSpectators(User& user);
        const std::vector<Game::User>& getUsers() const;
        void terminateGame(void);
        const Game::GameProperties& getProperties(void) const;

    // attributes
    private:
        Game::OnGameEvent *mListener;
        Timer mTimer;
        Game::GameProperties mProperties;
        std::vector<Game::User> mUsers;
        std::vector<Game::Component> mComponents;
        bool mIsRunning;
        bool mAlreadyRunOneTime;
        std::shared_ptr<IMutex> mMutex;

};

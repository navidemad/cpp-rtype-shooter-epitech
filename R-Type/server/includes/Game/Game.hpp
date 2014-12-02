#pragma once

#include "IMutex.hpp"
#include "Timer.hpp"
#include "Client.hpp"
#include "NoCopyable.hpp"
#include "IResource.hpp"
#include "GameProperties.hpp"
#include "GameUser.hpp"
#include "GameComponent.hpp"

#include <string>
#include <memory>
#include <list>
#include <functional>

namespace NGame
{

    class Game : public NoCopyable {

        // ctor / dtor
    public:
        explicit Game(const NGame::Properties& properties);
        ~Game(void) = default;

        // events
    public:
        class OnGameEvent {
        public:
            virtual ~OnGameEvent(void) {}
            virtual void onTerminatedGame(const std::string &name) = 0;
        };
        void	    setListener(NGame::Game::OnGameEvent *listener);
        void        setOwner(const Peer& owner);
        const Peer& getOwner(void) const;

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
        bool outOfScreen(const NGame::Component& component);
        bool collisionTouch(const NGame::Component& component, const NGame::Component& obstacle) const;
        bool collisionWithBonus(const NGame::Component& component, const NGame::Component& obstacle);
        bool collisionWithBullet(const NGame::Component& component, const NGame::Component& obstacle);
        bool collisionWithMonster(const NGame::Component& component, const NGame::Component& obstacle);
        bool collision(const NGame::Component& component);

        // internal functions
    public:
        void fire(const Peer&);
        void move(const Peer&, IResource::Direction);
        int countUserByType(NGame::USER_TYPE type) const;
        std::vector<NGame::User>::iterator findUserByHost(const Peer &peer);
        std::vector<NGame::User>::iterator findUserById(uint64_t id);
        void tryAddPlayer(const NGame::User& user);
        void tryAddSpectator(const NGame::User& user);
        void addUser(NGame::USER_TYPE type, const Peer &peer, const std::string& pseudo);
        void delUser(const Peer &peer);
        void transferPlayerToSpectators(NGame::User& user);
        const std::vector<NGame::User>& getUsers() const;
        void terminateGame(void);
        const NGame::Properties& getProperties(void) const;

        // attributes
    private:
        NGame::Game::OnGameEvent *mListener;
        Timer mTimer;
        NGame::Properties mProperties;
        std::vector<NGame::User> mUsers;
        std::vector<NGame::Component> mComponents;
        bool mIsRunning;
        bool mAlreadyRunOneTime;
        std::shared_ptr<IMutex> mMutex;
        Peer mOwner;

    };

}

#pragma once

#include "IMutex.hpp"
#include "Timer.hpp"
#include "Client.hpp"
#include "NoCopyable.hpp"
#include "IResource.hpp"
#include "GameProperties.hpp"
#include "GameUser.hpp"
#include "GameComponent.hpp"
#include "IScriptCommand.hpp"

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
                virtual ~OnGameEvent(void) = default;
                virtual void onTerminatedGame(const std::string &name) = 0;
            };
        
        // pull function called by threadPool
        public:
            void pull(void);
        private:
            void check(void);
            void actions(void);
            void update(void);

        // getters
        public:
            bool isRunningGame(void) const;
            const Peer& getOwner(void) const;
            const std::vector<NGame::User>& getUsers() const;
            const NGame::Properties& getProperties(void) const;

        // setters
        public:
            void setListener(NGame::Game::OnGameEvent *listener);
            void setOwner(const Peer& owner);

        // utils
        private:
            void logInfo(const std::string &log);

        // static values
        private:
            struct tokenExec {
                IScriptCommand::Instruction	cmd;
                void						(NGame::Game::*ftPtr)();
            };
            static const NGame::Game::tokenExec tokenExecTab[];
            static const float XMAX;
            static const float YMAX;

        // check :: outOfScreen
        private:
            bool outOfScreen(const NGame::Component&);

        // check :: collision
        private:
            bool collision(const NGame::Component& component);
            bool collisionTouch(const NGame::Component&, const NGame::Component&) const;
            bool collisionWithBonus(const NGame::Component&, const NGame::Component&);
            bool collisionWithBullet(const NGame::Component&, const NGame::Component&);
            bool collisionWithMonster(const NGame::Component&, const NGame::Component&);

        // workflow STL
        private:
            int NGame::Game::countUserByType(NGame::USER_TYPE) const;
        public:
            std::vector<NGame::User>::iterator NGame::Game::findUserByHost(const Peer &);
            std::vector<NGame::User>::iterator NGame::Game::findUserById(uint64_t);

        // workflow internal game
        private:
            void NGame::Game::tryAddPlayer(const NGame::User&);
            void NGame::Game::tryAddSpectator(const NGame::User&);
            void NGame::Game::transferPlayerToSpectators(NGame::User &);
        public:
            void NGame::Game::addUser(NGame::USER_TYPE type, const Peer &, const std::string&);
            void NGame::Game::delUser(const Peer &);
            
        // workflow gaming fire + move
        public:
            void NGame::Game::fire(const Peer&);
            void NGame::Game::move(const Peer&, IResource::Direction);

        // workflow scripts actions
        private:
            void recvName(void);
            void recvRequire(void);
            void recvAction(void);
            void recvAddCron(void);
            void recvRemoveCron(void);

        // attributes
        private:
            NGame::Game::OnGameEvent *mListener;
            Timer mTimer;
		    std::vector<std::shared_ptr<IScriptCommand>> mCommands;
            NGame::Properties mProperties;
            std::vector<NGame::User> mUsers;
            std::vector<NGame::Component> mComponents;
            bool mIsRunning;
            bool mAlreadyRunOneTime;
            std::shared_ptr<IMutex> mMutex;
            Peer mOwner;

    };

}

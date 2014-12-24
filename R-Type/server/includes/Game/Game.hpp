#pragma once

#include "NoCopyable.hpp"

#include "IMutex.hpp"
#include "IResource.hpp"
#include "IScriptCommand.hpp"

#include "Client.hpp"
#include "Script.hpp"
#include "Properties.hpp"
#include "User.hpp"
#include "Component.hpp"
#include "Resources.hpp"
#include "PlayerCommunicationManager.hpp"

#include <ctime>
#include <string>
#include <memory>
#include <list>
#include <functional>

namespace NGame
{

    class Game : public NoCopyable {

        // ctor / dtor
    public:
        explicit Game(const NGame::Properties&, const std::shared_ptr<NGame::Script>&);
        ~Game(void) = default;

        // events
    public:
        class OnGameEvent {
        public:
            virtual ~OnGameEvent(void) = default;
            virtual void onRemovePeerFromWhiteList(const Peer&) = 0;
            virtual void onNotifyUsersComponentRemoved(const std::vector<NGame::User>, uint64_t) = 0;
            virtual void onNotifyUsersComponentAdded(const std::vector<NGame::User>, const NGame::Component&) = 0;
            virtual void onNotifyUserGainScore(const Peer &, uint64_t, const std::string &, uint64_t) = 0;
            virtual void onNotifyTimeElapsedPing(const Peer &, double) = 0;
        };

        // pull function called by threadPool
    public:
        void pull(void);
    private:
        void checkCollisions(void);
        void broadcastMap(void);
        void moveEntities(void);

        // static values
    public:
        enum class State {
            NOT_STARTED = 0,
            RUNNING,
            DONE
        };
    private:
        struct tokenExec {
            IScriptCommand::Instruction	commandCode;
            void						(NGame::Game::*fctPtr)(const IScriptCommand* command);
        };
        static const NGame::Game::tokenExec tokenExecTab[];

        // getters
    public:
        std::shared_ptr<NGame::Script>& getScript(void);
        NGame::Game::OnGameEvent* getListener(void);
        double getCurrentFrame();
        NGame::Properties& getProperties(void);
        std::vector<NGame::User>& getUsers(void);
        NGame::Game::State getState(void) const;
        const Peer& getOwner(void);
        bool getPullEnded(void);
        uint64_t getCurrentComponentMaxId(void);

        // setters
    public:
        void setListener(NGame::Game::OnGameEvent*);
        void setState(NGame::Game::State);
        void setOwner(const Peer&);
        void setPullEnded(bool);
        void setCurrentComponentMaxId(uint64_t);

        // utils
    private:
        void logInfo(const std::string &log) const;
        bool isStillRunning(void) const;
        void initTimer(void);

        // check :: collision
    private:
        bool collision(NGame::Component& component);
        bool collisionTouch(const NGame::Component&, const NGame::Component&) const;
        bool collisionWithNoLife(NGame::Component& component);
        bool collisionWithBonus(NGame::Component&, NGame::Component&);
        bool collisionWithBullet(NGame::Component&, NGame::Component&);
        bool collisionWithEnnemy(NGame::Component&, NGame::Component&);

    public:
        NGame::User& findUserByHost(const Peer &);
        NGame::User& findUserById(uint64_t id);
        NGame::Component& findComponentById(uint64_t id);
        std::vector<NGame::User>::iterator NGame::Game::findIteratorUserByHost(const Peer &peer);

        // workflow internal game
    private:
        void addComponentInList(const NGame::Component&);
        void addUserInList(const NGame::User&);
        void eraseUserOfList(std::vector<NGame::User>::iterator& it);
        void tryAddPlayer(NGame::User&);
        void tryDelPlayer(void);
        void tryAddSpectator(const NGame::User&);
        void tryDelSpectator(void);
        void transferPlayerToSpectators(NGame::User &);
        void updatePositionComponent(NGame::Component&);

    public:
        void addUser(NGame::USER_TYPE type, const Peer &, const std::string&);
        void delUser(const Peer &);

        // workflow gaming fire + move
    public:
        NGame::Component fire(const Peer &);
        const NGame::Component& move(const Peer &, IResource::Direction);

        // workflow scripts actions
    private:
        void scriptCommandName(const IScriptCommand* command);
        void scriptCommandRequire(const IScriptCommand* command);
        void scriptCommandSpawn(const IScriptCommand* command);

        // attributes
    private:
        NGame::Resources mResources;
        NGame::Properties mProperties;
        NGame::Game::State mState;
        std::shared_ptr<NGame::Script> mScript;
        unsigned int mIndex;
        NGame::Game::OnGameEvent *mListener;
        std::clock_t mTimer;
        std::clock_t mLastTime;
        std::vector<NGame::User> mUsers;
        std::vector<NGame::Component> mComponents;
        std::shared_ptr<IMutex> mMutex;
        Peer mOwner;
        bool mPullEnded;
        uint64_t mCurrentComponentMaxId;

    };

}

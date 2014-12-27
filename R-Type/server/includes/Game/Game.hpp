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
#include "PlayerCommunicationManager.hpp"

#include <ctime>
#include <map>
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
            virtual void onNotifyUsersComponentRemoved(const std::vector<std::shared_ptr<NGame::User>> &, uint64_t) = 0;
            virtual void onNotifyUsersComponentAdded(const std::vector<std::shared_ptr<NGame::User>> &, const std::shared_ptr<NGame::Component>&) = 0;
            virtual void onNotifyUserGainScore(const Peer &, uint64_t, const std::string &, uint64_t) = 0;
            virtual void onNotifyTimeElapsedPing(const Peer &, float) = 0;
        };

        // pull function called by threadPool
    public:
        void pull(void);
    private:
        void resolvCollisions(void);
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
        static const std::map<std::string, std::string> ressourcesTab[];

        // getters
    public:
        NGame::Game::OnGameEvent* getListener(void) const;
        float getCurrentFrame() const;
        NGame::Properties& getProperties(void);
        std::vector<std::shared_ptr<NGame::User>>& getUsers(void);
        NGame::Game::State getState(void) const;
        const Peer& getOwner(void) const;
        bool getPullEnded(void) const;
        uint64_t getCurrentComponentMaxId(void) const;

        // setters
    public:
        void setListener(NGame::Game::OnGameEvent*);
        void setState(NGame::Game::State);
        void setOwner(const Peer&);
        void setPullEnded(bool);
        void setCurrentComponentMaxId(uint64_t);

        // utils
    private:
        void loadDll(void);
        void logInfo(const std::string &log) const;
        void initTimer(void);

        // check :: collision
    private:
        bool needRemove(const std::shared_ptr<NGame::Component>& c1);
        bool outScreen(const std::shared_ptr<NGame::Component>& c1) const;
        bool handleCollision(const std::shared_ptr<NGame::Component>& c1, const std::shared_ptr<NGame::Component>& c2);
        bool handleCollisionBonus(const std::shared_ptr<NGame::Component>& c1, const std::shared_ptr<NGame::Component>& c2);
        bool handleCollisionBullet(const std::shared_ptr<NGame::Component>& c1, const std::shared_ptr<NGame::Component>& c2);
        bool handleCollisionPlayer(const std::shared_ptr<NGame::Component>& c1, const std::shared_ptr<NGame::Component>& c2);
        bool handleCollisionMonster(const std::shared_ptr<NGame::Component>& c1, const std::shared_ptr<NGame::Component>& c2);

    public:
        std::shared_ptr<NGame::User>& findUserByHost(const Peer &);
        std::shared_ptr<NGame::User>& findUserById(uint64_t id);
        std::shared_ptr<NGame::Component>& findComponentById(uint64_t id);
        std::shared_ptr<NGame::Component>& findComponentByOwnerId(uint64_t id);
        std::vector<std::shared_ptr<NGame::User>>::iterator findIteratorUserByHost(const Peer &peer);

        // workflow internal game
    private:
        void spawn(const std::string& name, float x, float y, float angle, const std::shared_ptr<NGame::User>& owner);
        void addComponentInList(const std::shared_ptr<NGame::Component>&);
        float spawnX(void) const;
        float spawnY(void) const;
        void addUserInList(const std::shared_ptr<NGame::User>&);
        void transferPlayerToSpectators(std::shared_ptr<NGame::User> &);

    public:
        void addUser(NGame::USER_TYPE type, const Peer &, const std::string&);
        void delUser(const Peer &);

        // workflow gaming fire + move
    public:
        void fire(const Peer &);
        void move(const Peer &, IResource::Direction);

        // workflow scripts actions
    private:
        void scriptCommandSpawn(const IScriptCommand* command);

        // attributes
    private:
        static std::map<IResource::Type, std::string> mDLLoader;
        NGame::Timer mScriptTimer;
        NGame::Properties mProperties;
        NGame::Game::State mState;
        std::shared_ptr<NGame::Script> mScript;
        NGame::Game::OnGameEvent *mListener;
        std::vector<std::shared_ptr<NGame::User>> mUsers;
        std::vector<std::shared_ptr<NGame::Component>> mComponents;
        std::shared_ptr<IMutex> mMutex;
        Peer mOwner;
        bool mPullEnded;
        uint64_t mCurrentComponentMaxId;

    };

}

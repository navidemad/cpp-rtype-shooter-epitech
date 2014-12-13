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
#include "Script.hpp"
#include "PlayerCommunicationManager.hpp"

#include <string>
#include <memory>
#include <list>
#include <functional>

namespace NGame
{

    class Game : public NoCopyable {

        // ctor / dtor
        public:
            explicit Game(const NGame::Properties& properties, const Script&);
            ~Game(void) = default;

        // events
        public:
            class OnGameEvent {
            public:
                virtual ~OnGameEvent(void) = default;
				virtual void onRemovePeerFromWhiteList(const Peer&) = 0;
				virtual void onNotifyUsersComponentRemoved(const std::vector<NGame::User>&, uint64_t) = 0;
				virtual void onNotifyUserGainScore(const Peer &, uint64_t, const std::string &, uint64_t) = 0;
				virtual void onNotifyTimeElapsedPing(const Peer &, double) = 0;
            };
        
        // pull function called by threadPool
        public:
            void pull(void);
        private:
            void check(void);
            void actions(void);
            void update(void);

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
				void						(NGame::Game::*fctPtr)(const std::shared_ptr<IScriptCommand> &command);
			};
			struct tokenAngle {
				IResource::Direction		directionCode;
				short						angle;
			};
			static const NGame::Game::tokenExec tokenExecTab[];
			static const NGame::Game::tokenAngle tokenAngleTab[];
			static const double XMAX;
			static const double YMAX;
			static const double FRAMES_PER_SEC;
			static const uint64_t START_ID_COMPONENT;

        // getters
        public:
			NGame::Game::State getState(void) const;
			uint64_t getCurrentComponentMaxId(void) const;
			const Peer& getOwner(void) const;
            const std::vector<NGame::User>& getUsers() const;
            const NGame::Properties& getProperties(void) const;
            bool pullEnded(void) const;

        // setters
        public:
            void setListener(NGame::Game::OnGameEvent *listener);
            void setOwner(const Peer& owner);
            void setPullEnded(bool pullEnded);

        // utils
        private:
            void logInfo(const std::string &log) const;

        // check :: collision
        private:
            bool collision(NGame::Component& component);
            bool collisionTouch(const NGame::Component&, const NGame::Component&) const;
			bool collisionWithNoLife(NGame::Component& component);
			bool collisionWithBorders(NGame::Component& component);
            bool collisionWithBonus(NGame::Component&, NGame::Component&);
            bool collisionWithBullet(NGame::Component&, NGame::Component&);
            bool collisionWithEnnemy(NGame::Component&, NGame::Component&);

        // workflow STL
        private:
            int countUserByType(NGame::USER_TYPE) const;

        public:
            std::vector<NGame::User>::iterator findUserByHost(const Peer &);
            std::vector<NGame::User>::iterator findUserById(uint64_t);
			std::vector<NGame::Component>::iterator findComponentById(uint64_t);

        // workflow internal game
        private:
			void cronSendPingToSyncronizeClientTimer(void) const;
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
            void scriptCommandName(const std::shared_ptr<IScriptCommand> &command);
            void scriptCommandRequire(const std::shared_ptr<IScriptCommand> &command);
            void scriptCommandAction(const std::shared_ptr<IScriptCommand> &command);
            void scriptCommandAddCron(const std::shared_ptr<IScriptCommand> &command);
            void scriptCommandRemoveCron(const std::shared_ptr<IScriptCommand> &command);

        // attributes
        private:
			Script mScript;
            NGame::Game::OnGameEvent *mListener;
            Timer mTimer;
            NGame::Properties mProperties;
            std::vector<NGame::User> mUsers;
            std::vector<NGame::Component> mComponents;
			NGame::Game::State mState;
            std::shared_ptr<IMutex> mMutex;
            Peer mOwner;
			bool mPullEnded;
			uint64_t mCurrentComponentMaxId;
    };

}

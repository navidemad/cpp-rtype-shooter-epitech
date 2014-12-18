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

#include <iostream>
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
                virtual void onNotifyUsersComponentAdded(const std::vector<NGame::User>&, const NGame::Component&) = 0;
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

        // getters
        public:
			Script& getScript(void);
			NGame::Game::OnGameEvent* getListener(void);
			Timer& getTimer(void);
			NGame::Properties& getProperties(void);
			std::vector<NGame::User>& getUsers(void);
			std::vector<NGame::Component>& getComponents(void);
			NGame::Game::State getState(void);
			std::shared_ptr<IMutex>& getMutex(void);
			Peer& getOwner(void);
			bool getPullEnded(void);
			uint64_t getCurrentComponentMaxId(void);

        // setters
        public:
			void setScript(Script&);
			void setListener(NGame::Game::OnGameEvent*);
			void setProperties(NGame::Properties&);
			void setUsers(std::vector<NGame::User>&);
			void setComponents(std::vector<NGame::Component>&);
			void setState(NGame::Game::State);
			void setMutex(std::shared_ptr<IMutex>&);
			void setOwner(const Peer&);
			void setPullEnded(bool);
			void setCurrentComponentMaxId(uint64_t);

        // utils
        private:
            void logInfo(const std::string &log) const;

        // check :: collision
        private:
            bool collision(NGame::Component& component);
            bool collisionTouch(const NGame::Component&, const NGame::Component&) const;
			bool collisionWithNoLife(NGame::Component& component);
            bool collisionWithBonus(NGame::Component&, NGame::Component&);
            bool collisionWithBullet(NGame::Component&, NGame::Component&);
            bool collisionWithEnnemy(NGame::Component&, NGame::Component&);

        // workflow STL
        private:
            int countUserByType(NGame::USER_TYPE);

        public:
            std::vector<NGame::User>::iterator findUserByHost(const Peer &);
            std::vector<NGame::User>::iterator findUserById(uint64_t);
			std::vector<NGame::Component>::iterator findComponentById(uint64_t);

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


        // overload << display
        public:
            friend std::ostream& operator << (std::ostream& os, std::shared_ptr<Game> rhs) {
                os <<
                    "[Game]" << std::endl <<
                    "  [mProperties]" << std::endl << 
                    "     - getName:          '" << rhs->getProperties().getName() << "'" << std::endl << 
                    "     - getLevelName:     '" << rhs->getProperties().getLevelName() << "'" << std::endl <<
                    "     - getNbPlayers:     '" << rhs->getProperties().getNbPlayers() << "'" << std::endl << 
                    "     - getMaxPlayers:    '" << rhs->getProperties().getMaxPlayers() << "'" << std::endl << 
                    "     - getNbSpectators:  '" << rhs->getProperties().getNbSpectators() << "'" << std::endl << 
                    "     - getMaxSpectators: '" << rhs->getProperties().getMaxSpectators() << "'" << std::endl <<
                    "  [mUsers => " << rhs->getUsers().size() << " rows]" << std::endl;
                    for (const auto& user: rhs->getUsers())
                        os << 
                    "    [User]" << std::endl <<
                    "      - getPeer.host:   '" << user.getPeer().host << "'" << std::endl <<
                    "      - getPeer.udpPort:   '" << user.getPeer().udpPort << "'" << std::endl <<
                    "      - getPeer.tcpPort:   '" << user.getPeer().tcpPort << "'" << std::endl <<
                    "      - getPseudo: '" << user.getPseudo() << "'" << std::endl <<
                    "      - getType:   '" << (user.getType() == NGame::USER_TYPE::PLAYER ? "PLAYER" : "SPECTATOR") << "'" << std::endl <<
                    "      - getId:     '" << user.getId() << "'" << std::endl <<
                    "      - getScore:  '" << user.getScore() << "'" << std::endl;
                return os;
            }
    };

}

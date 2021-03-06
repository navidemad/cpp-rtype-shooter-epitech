#pragma once

#include "NGame.hpp"
#include "Peer.hpp"
#include "Game.hpp"
#include "ThreadPool.hpp"
#include "IMutex.hpp"
#include "Utils.hpp"
#include "ScriptLoader.hpp"
#include "PlayerCommunicationManager.hpp"
#include "NoCopyable.hpp"

#include <string>
#include <memory>
#include <vector>

#include <mutex>

namespace NGame
{

    class Manager : public NoCopyable, public PlayerCommunicationManager::OnPlayerCommunicationManagerEvent, public NGame::Game::OnGameEvent {

        // ctor / dtor
        public:
            Manager(void);
            ~Manager(void);

        // entry point
        public:
            int run(void);
            void loopGames(void);

    	// player communication manager events
    	public:
    		void onPlayerFire(const Peer &peer);
    		void onPlayerMove(IResource::Direction direction, const Peer &peer);

        // game events
        public:
        // events
        public:
            class OnManagerEvent {
                public:
                    virtual ~OnManagerEvent(void) = default;
                    virtual void onEndGame(const std::string &gameName, const std::list<Peer> &gameUsers) = 0;
            };

    		void onRemovePeerFromWhiteList(const Peer&);
            void onNotifyUsersComponentRemoved(const std::vector<std::shared_ptr<NGame::User>> &, uint64_t);
            void onNotifyUsersComponentAdded(const std::vector<std::shared_ptr<NGame::User>> &, const std::shared_ptr<NGame::Component>&);
    		void onNotifyUserGainScore(const Peer &, uint64_t, const std::string &, uint64_t);
            void onNotifyTimeElapsedPing(const Peer &, float);

            void setListener(NGame::Manager::OnManagerEvent *listener);
    		void terminatedGame(const std::shared_ptr<NGame::Game>& game);

    	// network workflow utils functions
    	public:
            void createGame(const NGame::Properties&properties, const Peer &peer);
            void removeGame(const Peer &peer, const std::string&);
            void joinGame(NGame::USER_TYPE typeUser, const Peer &peer, const std::string &name, const std::string &pseudo = "Anonymous");
            void playGame(const Peer &peer, const std::string &name, const std::string &pseudo);
            void spectateGame(const Peer &peer, const std::string &name);
            void leaveGame(const Peer &peer);
    		void updatePseudo(const Peer &peer, const std::string &pseudo);

            const NGame::Properties &getGameProperties(const std::string &name);
            std::list<NGame::Properties> getGamesProperties(void);
    		std::list<std::string> getScriptsName(void) const;

    	// internal methods
    	private:
            void removeClientsFromWhitelist(const std::shared_ptr<NGame::Game>&);
            std::shared_ptr<NGame::Game> findGameByName(const std::string& name);
            std::shared_ptr<NGame::Game> findGameByHost(const Peer &peer);
    		void addGameInList(const std::shared_ptr<NGame::Game> &game);
    		void removeGameFromList(const std::shared_ptr<NGame::Game> &game);

        // scoped functions
        public:
            std::vector<std::shared_ptr<NGame::Game>>& getGames(void);

        // attributes
        private:
            std::shared_ptr<ThreadPool> mThreadPool;
            std::shared_ptr<IMutex> mMutex;
            Manager::OnManagerEvent *mListener;
    		ScriptLoader mScriptLoader;
            PlayerCommunicationManager mPlayerCommunicationManager;
            mutable std::vector<std::shared_ptr<NGame::Game>> mGames;

    };

}
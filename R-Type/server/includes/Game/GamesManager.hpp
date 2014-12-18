#pragma once

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

class GamesManager : public NoCopyable, public PlayerCommunicationManager::OnPlayerCommunicationManagerEvent, public NGame::Game::OnGameEvent {

    // ctor / dtor
    public:
        GamesManager(void);
        ~GamesManager(void);

    // entry point
    public:
        void run(void);

	// player communication manager events
	public:
		void onPlayerFire(const Peer &peer);
		void onPlayerMove(IResource::Direction direction, const Peer &peer);

    // game events
    public:
    // events
    public:
        class OnGamesManagerEvent {
            public:
                virtual ~OnGamesManagerEvent(void) {}
                virtual void onEndGame(const std::string &gameName, const std::list<Peer> &gameUsers) = 0;
        };

		void onRemovePeerFromWhiteList(const Peer&);
		void onNotifyUsersComponentRemoved(const std::vector<NGame::User>&, uint64_t);
        void onNotifyUsersComponentAdded(const std::vector<NGame::User>&, const NGame::Component&);
		void onNotifyUserGainScore(const Peer &, uint64_t, const std::string &, uint64_t);
		void onNotifyTimeElapsedPing(const Peer &, double);

        void    setListener(GamesManager::OnGamesManagerEvent *listener);
		std::vector<std::shared_ptr<NGame::Game>>::iterator terminatedGame(std::vector<std::shared_ptr<NGame::Game>>::iterator it);

	// network workflow utils functions
	public:
        void    createGame(const NGame::Properties&properties, const Peer &peer);
        void    removeGame(const Peer &peer, const std::string&);
        void    joinGame(NGame::USER_TYPE typeUser, const Peer &peer, const std::string &name, const std::string &pseudo = "Anonymous");
        void    playGame(const Peer &peer, const std::string &name, const std::string &pseudo);
        void    spectateGame(const Peer &peer, const std::string &name);
        void	leaveGame(const Peer &peer);
		void	updatePseudo(const Peer &peer, const std::string &pseudo);

        const NGame::Properties &getGameProperties(const std::string &name);
        std::list<NGame::Properties> getGamesProperties(void);
		std::list<std::string> getScriptsName(void) const;
		
	// internal methods
	private:
        void removeClientsFromWhitelist(const std::shared_ptr<NGame::Game>&);
		std::vector<std::shared_ptr<NGame::Game>>::iterator findGameByName(const std::string& name);
		std::vector<std::shared_ptr<NGame::Game>>::iterator findGameByHost(const Peer &peer);

    // scoped functions
    public:
        std::vector<std::shared_ptr<NGame::Game>>& getGames(void);
        const ScriptLoader& getScriptLoader(void) const;
        PlayerCommunicationManager& getPlayerCommunicationManager(void);
        GamesManager::OnGamesManagerEvent* getListener(void) const;
        void addGameToList(const std::shared_ptr<NGame::Game>&);
        std::vector<std::shared_ptr<NGame::Game>>::iterator removeItGameFromList(std::vector<std::shared_ptr<NGame::Game>>::iterator);

    // attributes
    private:
		ScriptLoader mScriptLoader;
		std::shared_ptr<ThreadPool> mThreadPool;
        std::vector<std::shared_ptr<NGame::Game>> mGames;
        std::shared_ptr<IMutex> mMutex;
		PlayerCommunicationManager mPlayerCommunicationManager;
        GamesManager::OnGamesManagerEvent *mListener;

};

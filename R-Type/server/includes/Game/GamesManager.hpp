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

class GamesManager : public NoCopyable, public PlayerCommunicationManager::OnPlayerCommunicationManagerEvent, public Game::OnGameEvent {

    // ctor / dtor
    public:
        explicit GamesManager(void);
        ~GamesManager(void);

    // entry point
    public:
        void run(void);

	// player communication manager events
	public:
		void onPlayerFire(const PlayerCommunicationManager &playerCommunicationManager, const Peer &peer);
		void onPlayerMove(const PlayerCommunicationManager &playerCommunicationManager, IResource::Direction direction, const Peer &peer);

    // game events
    public:
        void onTerminatedGame(const std::string &name);

	// network workflow utils functions
	public:
        void    createGame(const Game::GameProperties&properties, const Peer &peer);
        void    removeGame(const Peer &peer, const std::string&);
        void    joinGame(Game::USER_TYPE typeUser, const Peer &peer, const std::string &name, const std::string &pseudo = "Anonymous");
        void    playGame(const Peer &peer, const std::string &name, const std::string &pseudo);
        void    spectateGame(const Peer &peer, const std::string &name);
        void	leaveGame(const Peer &peer, bool throwExcept = true);
		void	updatePseudo(const Peer &peer, const std::string &pseudo);
		const Game::GameProperties &getGameProperties(const std::string &name);
		const std::list<Game::GameProperties> &getGamesProperties(void) const;
        std::vector<std::shared_ptr<Game>>::iterator findGameByGamePtr(const std::shared_ptr<Game>& target);
        std::vector<std::shared_ptr<Game>>::iterator findGameByName(const std::string& name);
        std::vector<std::shared_ptr<Game>>::iterator findGameByHost(const Peer &peer);

    // getter
    public:
        const ScriptLoader& getScriptLoader(void) const;

    // attributes
    private:
		ScriptLoader mScriptLoader;
		std::shared_ptr<ThreadPool> mThreadPool;
        std::vector<std::shared_ptr<Game>> mGames;
        std::shared_ptr<IMutex> mMutex;
		PlayerCommunicationManager mPlayerCommunicationManager;

};

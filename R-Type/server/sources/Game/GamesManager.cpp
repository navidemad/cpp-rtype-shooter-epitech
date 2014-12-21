#include "GamesManager.hpp"
#include "GameException.hpp"
#include "GamesManagerException.hpp"
#include "GameProperties.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include "Default.hpp"

#include <csignal>
#include <algorithm>
#include <functional>
#include <iostream>

GamesManager::GamesManager(void) : 
    mThreadPool(ThreadPool::getInstance()), 
    mMutex(PortabilityBuilder::getMutex()), mListener(nullptr)
{
	mPlayerCommunicationManager.setListener(this);
}

GamesManager::~GamesManager(void) 
{
    mGames.clear();
    mThreadPool->stop();
}

volatile std::sig_atomic_t interruptedSignal;
 
extern "C" void signal_handler(int signal)
{
    interruptedSignal = signal;
}

int GamesManager::run(void) {
    if (mScriptLoader.loadAll() == false)
    {
        std::cerr << "Cannot play if server haven't game's scripts" << std::endl;
        return EXIT_FAILURE;
    }

    if (std::signal(SIGINT, signal_handler) == SIG_ERR)
    {
        std::cerr << "Cannot set signal_handler" << std::endl;
        return EXIT_FAILURE;
    }

    while (!interruptedSignal)
        loopGames();

    return EXIT_SUCCESS;
}

void GamesManager::loopGames(void) {
    std::vector<std::shared_ptr<NGame::Game>> games = getGames();
    for (std::shared_ptr<NGame::Game> game : games) {
        if (game->getPullEnded() == true) {
            if (game->getState() == NGame::Game::State::RUNNING) {
                game->setPullEnded(false);
                *mThreadPool << std::bind(&NGame::Game::pull, game);
            }
            if (game->getState() == NGame::Game::State::DONE) {
                terminatedGame(game);
                return;
            }
        }
    }
}

void    GamesManager::setListener(GamesManager::OnGamesManagerEvent *listener) {
    mListener = listener;
}

std::vector<std::shared_ptr<NGame::Game>>& GamesManager::getGames(void) {
    std::lock_guard<std::mutex> guard(this->mMutexTest);
    return mGames;
}

void GamesManager::createGame(const NGame::Properties& properties, const Peer &peer) {
    try {
        findGameByName(properties.getName());
    }
    catch (const GamesManagerException&) {
        if (properties.getMaxPlayers() < 1 || properties.getMaxPlayers() > Config::Game::maxPlayersInAGame)
            throw GamesManagerException("Invalid max nb players", ErrorStatus(ErrorStatus::Error::KO));
        if (properties.getMaxSpectators() < 0 || properties.getMaxSpectators() > Config::Game::maxSpectatorsInAGame)
            throw GamesManagerException("Invalid max nb observers", ErrorStatus(ErrorStatus::Error::KO));
        if (mScriptLoader.has(properties.getLevelName()) == false)
            throw GamesManagerException("Invalid level name", ErrorStatus(ErrorStatus::Error::KO));
        auto game = std::make_shared<NGame::Game>(properties, mScriptLoader.get(properties.getLevelName()));
        game->setListener(this);
        game->setOwner(peer);
        {
            std::lock_guard<std::mutex> guard(this->mMutexTest);
            mGames.push_back(game);
        }
    }
}

void GamesManager::removeGame(const Peer &peer, const std::string& name) {
    try {
        const std::shared_ptr<NGame::Game>& gamebyname = findGameByName(name);
    	if (peer != gamebyname->getOwner())
            throw GamesManagerException("You can remove a game only if you are owner", ErrorStatus(ErrorStatus::Error::KO));
    	removeClientsFromWhitelist(gamebyname);
        gamebyname->setState(NGame::Game::State::DONE);      
    } catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::joinGame(NGame::USER_TYPE typeUser, const Peer &peer, const std::string &name, const std::string &pseudo) {
    try {
        findGameByHost(peer);
    }
    catch (const GamesManagerException&) {
        try {
            const std::shared_ptr<NGame::Game>& gamebyname = findGameByName(name);
            gamebyname->addUser(typeUser, peer, pseudo);   
        } 
        catch (const GameException& e) {
            throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
        }
    }
}

void GamesManager::playGame(const Peer &peer, const std::string &name, const std::string &pseudo) {
    try {
        joinGame(NGame::USER_TYPE::PLAYER, peer, name, pseudo);
        mPlayerCommunicationManager.addPeerToWhiteList(peer);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::spectateGame(const Peer &peer, const std::string &name) {
    try {
        joinGame(NGame::USER_TYPE::SPECTATOR, peer, name);
        mPlayerCommunicationManager.removePeerFromWhiteList(peer);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::leaveGame(const Peer &peer) {
    try {
        const std::shared_ptr<NGame::Game>& gamebyhost = findGameByHost(peer);
        gamebyhost->delUser(peer);
        mPlayerCommunicationManager.removePeerFromWhiteList(peer);
    } catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::updatePseudo(const Peer &peer, const std::string &pseudo) {
    try {
        const std::shared_ptr<NGame::Game>& gamebyhost = findGameByHost(peer);
        NGame::User& user = gamebyhost->findUserByHost(peer);
        user.setPseudo(pseudo);
    } catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

/*
** PlayerCommunicationManager::OnPlayerCommunicationManagerEvent
*/ 
void GamesManager::onPlayerFire(const Peer &peer) {
    try {
        const std::shared_ptr<NGame::Game>& gamebyhost = findGameByHost(peer);
        NGame::Component component = gamebyhost->fire(peer);
        const std::vector<NGame::User>& users = gamebyhost->getUsers();
        for (const auto& user : users)
           mPlayerCommunicationManager.sendMoveResource(user.getPeer(), component.getId(), component.getType(), component.getX(), component.getY(), component.getAngle());
    } catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::onPlayerMove(IResource::Direction direction, const Peer &peer) {
    try {
        const std::shared_ptr<NGame::Game>& gamebyhost = findGameByHost(peer);
        const NGame::Component& component = gamebyhost->move(peer, direction);
        const std::vector<NGame::User>& users = gamebyhost->getUsers();
        for (const auto& user : users)
           mPlayerCommunicationManager.sendMoveResource(user.getPeer(), component.getId(), component.getType(), component.getX(), component.getY(), component.getAngle());
    } catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

/*
** Game::OnGameEvent
*/
void GamesManager::terminatedGame(const std::shared_ptr<NGame::Game>& game) {
    std::list<Peer> peerUsers;
    const std::vector<NGame::User>& gameUsers = game->getUsers();
    for (const auto& user : gameUsers) {
        onNotifyUserGainScore(user.getPeer(), user.getId(), user.getPseudo(), user.getScore());
        peerUsers.push_back(user.getPeer());
    }

    if (mListener)
        mListener->onEndGame(game->getProperties().getName(), peerUsers);

    removeClientsFromWhitelist(game);

    {
        std::lock_guard<std::mutex> guard(this->mMutexTest);
        mGames.erase(std::remove(mGames.begin(), mGames.end(), game), mGames.end());
    }
}

void GamesManager::onRemovePeerFromWhiteList(const Peer& peer) {
    mPlayerCommunicationManager.removePeerFromWhiteList(peer);
}

void GamesManager::onNotifyUsersComponentRemoved(const std::vector<NGame::User>& users, uint64_t id) {
    for (const auto& user : users)
        mPlayerCommunicationManager.sendDestroyResource(user.getPeer(), id);
}

void GamesManager::onNotifyUsersComponentAdded(const std::vector<NGame::User>& users, const NGame::Component& component) {
    for (const auto& user : users)
        mPlayerCommunicationManager.sendMoveResource(user.getPeer(), component.getId(), component.getType(), component.getX(), component.getY(), component.getAngle());
}

void GamesManager::onNotifyUserGainScore(const Peer &peer, uint64_t id, const std::string &pseudo, uint64_t score) {
    mPlayerCommunicationManager.sendUpdateScore(peer, id, pseudo, score);
}

void GamesManager::onNotifyTimeElapsedPing(const Peer &peer, double elapsedPing) {
    mPlayerCommunicationManager.sendTimeElapsedPing(peer, elapsedPing);
}

void    GamesManager::removeClientsFromWhitelist(const std::shared_ptr<NGame::Game> &game) {
    const std::vector<NGame::User>& gameUsers = game->getUsers();
    std::for_each(gameUsers.begin(), gameUsers.end(), [&](const NGame::User& user) {
        mPlayerCommunicationManager.removePeerFromWhiteList(user.getPeer());
    });
}

const NGame::Properties &GamesManager::getGameProperties(const std::string &name) {
    const std::shared_ptr<NGame::Game>& gamebyname = findGameByName(name);
    return gamebyname->getProperties();
}

std::list<NGame::Properties> GamesManager::getGamesProperties(void) {
	std::list<NGame::Properties> gamesProperties;

    std::vector<std::shared_ptr<NGame::Game>> games = getGames();
    for (const auto& game : games)
        gamesProperties.push_back(game->getProperties());

    return gamesProperties;
}

const std::shared_ptr<NGame::Game>& GamesManager::findGameByName(const std::string& name) {
    const std::vector<std::shared_ptr<NGame::Game>>& games = getGames();
    for (const std::shared_ptr<NGame::Game>& game : games)
        if (game->getProperties().getName() == name)
            return game;
    throw GamesManagerException("findGameByName doesn't match", ErrorStatus(ErrorStatus::Error::KO));
}

const std::shared_ptr<NGame::Game>& GamesManager::findGameByHost(const Peer &peer) {
    const std::vector<std::shared_ptr<NGame::Game>>& games = getGames();
    for (const std::shared_ptr<NGame::Game>& game : games) {
        const std::vector<NGame::User>& users = game->getUsers();
        if (users.size() != 0)
            for (auto& user: users)
                if (user.getPeer() == peer)
                    return game;
    }
    throw GamesManagerException("findGameByName doesn't match", ErrorStatus(ErrorStatus::Error::KO));
}

std::list<std::string> GamesManager::getScriptsName(void) const {
	std::list<std::string> scriptsName;

	for (const auto& script : mScriptLoader.getScripts())
		scriptsName.push_back(script.first);

	return scriptsName;
}

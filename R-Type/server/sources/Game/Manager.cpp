#include "Manager.hpp"
#include "GameException.hpp"
#include "GamesManagerException.hpp"
#include "Properties.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include "Default.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <functional>
#include <iostream>

NGame::Manager::Manager(void) :
    mThreadPool(ThreadPool::getInstance()),
    mMutex(PortabilityBuilder::getMutex()), mListener(nullptr)
{
	mPlayerCommunicationManager.setListener(this);
}

NGame::Manager::~Manager(void)
{
    mGames.clear();
}

int NGame::Manager::run(void) {
    if (mScriptLoader.loadAll() == false)
    {
        std::cerr << "Cannot play if server haven't game's scripts" << std::endl;
        return EXIT_FAILURE;
    }

    while (!Utils::interruptedSignal)
        loopGames();

    return EXIT_SUCCESS;
}

void NGame::Manager::loopGames(void) {
    std::vector<std::shared_ptr<NGame::Game>> games = getGames();
    for (const auto &game : games) {
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

void    NGame::Manager::setListener(NGame::Manager::OnManagerEvent *listener) {
    mListener = listener;
}

std::vector<std::shared_ptr<NGame::Game>>& NGame::Manager::getGames(void) {
	ScopedLock scopedlock(mMutex);

	return mGames;
}

void NGame::Manager::addGameInList(const std::shared_ptr<NGame::Game> &game) {
	ScopedLock scopedlock(mMutex);

	mGames.push_back(game);
}

void NGame::Manager::createGame(const NGame::Properties& properties, const Peer &peer) {
    try {
        findGameByName(properties.getName());
    }
    catch (const GamesManagerException&) {
        if (properties.getMaxPlayers() < 1 || properties.getMaxPlayers() > Config::Game::maxPlayersInAGame)
            throw GamesManagerException("Invalid max nb players: requested '" + Utils::toString<int>(properties.getMaxPlayers()), ErrorStatus(ErrorStatus::Error::KO));
        if (properties.getMaxSpectators() < 0 || properties.getMaxSpectators() > Config::Game::maxSpectatorsInAGame)
            throw GamesManagerException("Invalid max nb observers: requested '" + Utils::toString<int>(properties.getMaxSpectators()), ErrorStatus(ErrorStatus::Error::KO));
        if (mScriptLoader.has(properties.getLevelName()) == false)
            throw GamesManagerException("Invalid level name: requested '" + properties.getLevelName(), ErrorStatus(ErrorStatus::Error::KO));

		auto game = std::make_shared<NGame::Game>(properties, mScriptLoader.get(properties.getLevelName()));
        game->setListener(this);
        game->setOwner(peer);
		addGameInList(game);
    }
}

void NGame::Manager::removeGame(const Peer &peer, const std::string& name) {
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

void NGame::Manager::joinGame(NGame::USER_TYPE typeUser, const Peer &peer, const std::string &name, const std::string &pseudo) {
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

void NGame::Manager::playGame(const Peer &peer, const std::string &name, const std::string &pseudo) {
    try {
        joinGame(NGame::USER_TYPE::PLAYER, peer, name, pseudo);
        mPlayerCommunicationManager.addPeerToWhiteList(peer);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void NGame::Manager::spectateGame(const Peer &peer, const std::string &name) {
    try {
        joinGame(NGame::USER_TYPE::SPECTATOR, peer, name);
        mPlayerCommunicationManager.removePeerFromWhiteList(peer);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void NGame::Manager::leaveGame(const Peer &peer) {
    try {
        const std::shared_ptr<NGame::Game>& gamebyhost = findGameByHost(peer);
        gamebyhost->delUser(peer);
        mPlayerCommunicationManager.removePeerFromWhiteList(peer);
    } catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void NGame::Manager::updatePseudo(const Peer &peer, const std::string &pseudo) {
    try {
        const std::shared_ptr<NGame::Game>& gamebyhost = findGameByHost(peer);
        std::shared_ptr<NGame::User>& user = gamebyhost->findUserByHost(peer);
        user->setPseudo(pseudo);
    } catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

/*
** PlayerCommunicationManager::OnPlayerCommunicationManagerEvent
*/
void NGame::Manager::onPlayerFire(const Peer &peer) {
    try {
        const std::shared_ptr<NGame::Game>& gamebyhost = findGameByHost(peer);
        gamebyhost->fire(peer);
    } catch (const GameException&) {
    }
}

void NGame::Manager::onPlayerMove(IResource::Direction direction, const Peer &peer) {
    try {
        const std::shared_ptr<NGame::Game>& gamebyhost = findGameByHost(peer);
        gamebyhost->move(peer, direction);
    } catch (const GameException&) {
    }
}

void NGame::Manager::removeGameFromList(const std::shared_ptr<NGame::Game> &game) {
	ScopedLock scopedlock(mMutex);

	mGames.erase(std::remove(mGames.begin(), mGames.end(), game), mGames.end());
}

/*
** Game::OnGameEvent
*/
void NGame::Manager::terminatedGame(const std::shared_ptr<NGame::Game>& game) {
    std::list<Peer> peerUsers;
    std::vector<std::shared_ptr<NGame::User>> gameUsers = game->getUsers();
    for (const auto& user : gameUsers) {
        onNotifyUserGainScore(user->getPeer(), user->getId(), user->getPseudo(), user->getScore());
        peerUsers.push_back(user->getPeer());
    }

    if (mListener)
        mListener->onEndGame(game->getProperties().getName(), peerUsers);

    removeClientsFromWhitelist(game);
	removeGameFromList(game);
}

void NGame::Manager::onRemovePeerFromWhiteList(const Peer& peer) {
    mPlayerCommunicationManager.removePeerFromWhiteList(peer);
}

void NGame::Manager::onNotifyUsersComponentRemoved(const std::vector<std::shared_ptr<NGame::User>> &users, uint64_t id) {
    for (auto user : users)
        mPlayerCommunicationManager.sendDestroyResource(user->getPeer(), id);
}

void NGame::Manager::onNotifyUsersComponentAdded(const std::vector<std::shared_ptr<NGame::User>> &users, const std::shared_ptr<NGame::Component>& component) {
    for (auto user : users)
        mPlayerCommunicationManager.sendMoveResource(user->getPeer(), component->getId(), component->getType(), component->getX(), component->getY(), component->getAngle());
}

void NGame::Manager::onNotifyUserGainScore(const Peer &peer, uint64_t id, const std::string &pseudo, uint64_t score) {
    mPlayerCommunicationManager.sendUpdateScore(peer, id, pseudo, score);
}

void NGame::Manager::onNotifyTimeElapsedPing(const Peer &peer, double elapsedPing) {
    mPlayerCommunicationManager.sendTimeElapsedPing(peer, elapsedPing);
}

void    NGame::Manager::removeClientsFromWhitelist(const std::shared_ptr<NGame::Game> &game) {
    std::vector<std::shared_ptr<NGame::User>> gameUsers = game->getUsers();

    std::for_each(gameUsers.begin(), gameUsers.end(), [&](const std::shared_ptr<NGame::User>& user) {
        mPlayerCommunicationManager.removePeerFromWhiteList(user->getPeer());
    });
}

const NGame::Properties &NGame::Manager::getGameProperties(const std::string &name) {
    const std::shared_ptr<NGame::Game>& gamebyname = findGameByName(name);
    return gamebyname->getProperties();
}

std::list<NGame::Properties> NGame::Manager::getGamesProperties(void) {
	std::list<NGame::Properties> gamesProperties;

    std::vector<std::shared_ptr<NGame::Game>> games = getGames();
    for (const auto &game : games)
        gamesProperties.push_back(game->getProperties());

    return gamesProperties;
}

std::shared_ptr<NGame::Game> NGame::Manager::findGameByName(const std::string& name) {
    std::vector<std::shared_ptr<NGame::Game>> games = getGames();
    for (const auto& game : games)
        if (game->getProperties().getName() == name)
            return game;
    throw GamesManagerException("findGameByName doesn't match", ErrorStatus(ErrorStatus::Error::KO));
}

std::shared_ptr<NGame::Game> NGame::Manager::findGameByHost(const Peer &peer) {
    std::vector<std::shared_ptr<NGame::Game>> games = getGames();
    for (const std::shared_ptr<NGame::Game>& game : games) {
        std::vector<std::shared_ptr<NGame::User>> users = game->getUsers();
        if (users.size() != 0)
            for (const auto &user: users)
                if (user->getPeer() == peer)
                    return game;
    }
    throw GamesManagerException("findGameByName doesn't match", ErrorStatus(ErrorStatus::Error::KO));
}

std::list<std::string> NGame::Manager::getScriptsName(void) const {
	std::list<std::string> scriptsName;

	for (const auto& script : mScriptLoader.getScripts())
		scriptsName.push_back(script.first);

	return scriptsName;
}

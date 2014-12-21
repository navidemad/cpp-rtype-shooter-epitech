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

void    GamesManager::setListener(GamesManager::OnGamesManagerEvent *listener) {
    mListener = listener;
}

/*
-------------------  scoped functions --------------------------
*/

std::vector<std::shared_ptr<NGame::Game>>& GamesManager::getGames(void) {
    std::lock_guard<std::mutex> guard(this->mMutexTest);
    //Scopedlock(mMutex);

    return mGames;
}

void GamesManager::addGameToList(const std::shared_ptr<NGame::Game>& game) {
    std::lock_guard<std::mutex> guard(this->mMutexTest);
    //Scopedlock(mMutex);

    mGames.push_back(game);
}

void GamesManager::removeItGameFromList(std::vector<std::shared_ptr<NGame::Game>>::iterator it_game) {
    std::lock_guard<std::mutex> guard(this->mMutexTest);
    //Scopedlock(mMutex);

    mGames.erase(it_game);
}

/*
------------------- OTHERS --------------------------
*/
GamesManager::GamesManager(void) : mThreadPool(ThreadPool::getInstance()), mMutex(PortabilityBuilder::getMutex()), mListener(nullptr) {
	mPlayerCommunicationManager.setListener(this);
}

GamesManager::~GamesManager(void) {
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
    auto games = getGames();
    for (auto it = games.begin(); it != games.end();)
    {
        if ((*it)->getPullEnded() == true)
        {
            if ((*it)->getState() == NGame::Game::State::RUNNING)
            {
                (*it)->setPullEnded(false);
                *mThreadPool << std::bind(&NGame::Game::pull, (*it));
            }
            if ((*it)->getState() == NGame::Game::State::DONE)
            {
                terminatedGame(findGameByName((*it)->getProperties().getName()));
                loopGames();
                return;
            }
        }
        ++it;
    }
}

void GamesManager::createGame(const NGame::Properties& properties, const Peer &peer) {
    if (findGameByName(properties.getName()) != getGames().end())
		throw GamesManagerException("Game name already taken", ErrorStatus(ErrorStatus::Error::KO));
    if (properties.getMaxPlayers() < 1 || properties.getMaxPlayers() > Config::Game::maxPlayersInAGame)
		throw GamesManagerException("Invalid max nb players", ErrorStatus(ErrorStatus::Error::KO));
    if (properties.getMaxSpectators() < 0 || properties.getMaxSpectators() > Config::Game::maxSpectatorsInAGame)
		throw GamesManagerException("Invalid max nb observers", ErrorStatus(ErrorStatus::Error::KO));
    if (mScriptLoader.has(properties.getLevelName()) == false)
		throw GamesManagerException("Invalid level name", ErrorStatus(ErrorStatus::Error::KO));
	auto game = std::make_shared<NGame::Game>(properties, mScriptLoader.get(properties.getLevelName()));

    game->setListener(this);
    game->setOwner(peer);

    addGameToList(game);
}

void GamesManager::removeGame(const Peer &peer, const std::string& name) {
    const auto& game = findGameByName(name);

    if (game == getGames().end())
        throw GamesManagerException("Try to delete an undefined game", ErrorStatus(ErrorStatus::Error::KO));

	if (peer == (*game)->getOwner()) {
		removeClientsFromWhitelist(*game);
        removeItGameFromList(game);
	}
    else
        throw GamesManagerException("You can remove a game only if you are owner", ErrorStatus(ErrorStatus::Error::KO));
}

void GamesManager::joinGame(NGame::USER_TYPE typeUser, const Peer &peer, const std::string &name, const std::string &pseudo) {
    auto games = getGames();
    auto it_game = findGameByHost(peer);
    auto it_end = games.end();

    if (it_game != it_end)
        throw GamesManagerException("User is already in a game", ErrorStatus(ErrorStatus::Error::KO));

    const auto& game = findGameByName(name);
    if (game == it_end)
        throw GamesManagerException("Try to join an undefined game party name", ErrorStatus(ErrorStatus::Error::KO));

    (*game)->addUser(typeUser, peer, pseudo);
    std::cout << (*game) << std::endl; // DEBUG
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
        auto game = findGameByHost(peer);

        if (game == getGames().end()) // exception getGames
            throw GamesManagerException("Try to leave a player who isn't in a game", ErrorStatus(ErrorStatus::Error::KO));

        (*game)->delUser(peer);
        mPlayerCommunicationManager.removePeerFromWhiteList(peer);
    } catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::updatePseudo(const Peer &peer, const std::string &pseudo) {
    auto game = findGameByHost(peer);

    if (game == getGames().end())
        throw GamesManagerException("Try to update pseudo of a non-existing player", ErrorStatus(ErrorStatus::Error::KO));

    try {
        auto user = (*game)->findUserByHost(peer);
        if (user == (*game)->getUsers().end())
            throw GameException("Try to update pseudo of a non-existing player");
        user->setPseudo(pseudo);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

/*
** PlayerCommunicationManager::OnPlayerCommunicationManagerEvent
*/ 
void GamesManager::onPlayerFire(const Peer &peer) {
    try {
        auto game = findGameByHost(peer);

        if (game == getGames().end())
            throw GamesManagerException("Try to fire a player that is not in a game", ErrorStatus(ErrorStatus::Error::KO));
        
        try {
            auto component = (*game)->fire(peer);
            auto users = (*game)->getUsers();
            for (const auto& user : users)
                mPlayerCommunicationManager.sendMoveResource(user.getPeer(), component.getId(), component.getType(), component.getX(), component.getY(), component.getAngle());
        }
        catch (const GameException& e) {
            std::cerr << "GameException caught: " << e.what() << std::endl;
        }
    }
    catch (const GamesManagerException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GamesManager::onPlayerMove(IResource::Direction direction, const Peer &peer) {
    try {
        auto game = findGameByHost(peer);

        if (game == getGames().end())
            throw GamesManagerException("Try to move a player that is not in a game", ErrorStatus(ErrorStatus::Error::KO));

        try {
            auto& component = (*game)->move(peer, direction);
            for (const auto& user : (*game)->getUsers())
                mPlayerCommunicationManager.sendMoveResource(user.getPeer(), component.getId(), component.getType(), component.getX(), component.getY(), component.getAngle());
        }
        catch (const GameException& e) {
            std::cerr << "GameException caught: " << e.what() << std::endl;
        }
    }
    catch (const GamesManagerException& e) {
        std::cerr << e.what() << std::endl;
    }
}

/*
** Game::OnGameEvent
*/
void GamesManager::terminatedGame(std::vector<std::shared_ptr<NGame::Game>>::iterator it) {
    std::list<Peer> gameUsers;

    for (const auto& user : (*it)->getUsers()) {
        onNotifyUserGainScore(user.getPeer(), user.getId(), user.getPseudo(), user.getScore());
        gameUsers.push_back(user.getPeer());
    }

    if (mListener)
        mListener->onEndGame((*it)->getProperties().getName(), gameUsers);

    removeClientsFromWhitelist(*it);
    removeItGameFromList(it);
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
    const auto& usersInGame = game->getUsers();
    std::for_each(usersInGame.begin(), usersInGame.end(), [&](const NGame::User& user) {
        mPlayerCommunicationManager.removePeerFromWhiteList(user.getPeer());
    });
}

const NGame::Properties &GamesManager::getGameProperties(const std::string &name) {
    const auto& game = findGameByName(name);

    if (game == getGames().end())
        throw GamesManagerException("Try to get properties of an undefined game", ErrorStatus(ErrorStatus::Error::KO));

    return (*game)->getProperties();
}

std::list<NGame::Properties> GamesManager::getGamesProperties(void) {
	std::list<NGame::Properties> gamesProperties;

    auto games = getGames();
    for (const auto& game : games)
        gamesProperties.push_back(game->getProperties());

    return gamesProperties;
}

std::vector<std::shared_ptr<NGame::Game>>::iterator GamesManager::findGameByName(const std::string& name) {
    auto games = getGames();
    auto it = games.begin();
    while (it != games.end())
    {
        if ((*it)->getProperties().getName() == name)
            return it;
        ++it;
    }
    return it;
}

std::vector<std::shared_ptr<NGame::Game>>::iterator GamesManager::findGameByHost(const Peer &peer) {
    auto games = getGames();
    auto it = games.begin();
    while (it != games.end())
    {
        auto users = (*it)->getUsers();
        if (users.size() != 0)
            for (auto& user: users)
                if (user.getPeer() == peer)
                    return it;
        ++it;
    }
    return it;
}

std::list<std::string> GamesManager::getScriptsName(void) const {
	std::list<std::string> scriptsName;

	for (const auto& script : mScriptLoader.getScripts())
		scriptsName.push_back(script.first);

	return scriptsName;
}

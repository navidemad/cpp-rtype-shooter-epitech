#include "GamesManager.hpp"
#include "GamesManagerException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"

#include <algorithm>
#include <iostream>

GamesManager::GamesManager(void) : mThreadPool(ThreadPool::getInstance()), mMutex(PortabilityBuilder::getMutex()) {
	mPlayerCommunicationManager.setListener(this);
}

GamesManager::~GamesManager(void) {
    mGames.clear();
}


void GamesManager::run(void) {
	mScriptLoader.loadAll();

    for (;;) for (const auto &game : mGames) {
        *mThreadPool << std::bind(&Game::updatePositions, game);
        *mThreadPool << std::bind(&Game::checkRessources, game);
    }
}

void GamesManager::createGame(const Game::GameProperties& properties, const std::string& host) {
    ScopedLock scopedLock(mMutex);

    auto game = std::shared_ptr<Game>{ std::make_shared<Game>(properties, host) };
    game->setListener(this);
    mGames.push_back(game);
}

void GamesManager::removeGame(const std::string& name) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByName(name);

    if (game == mGames.end())
        throw GamesManagerException("Try to delete an undefined game", ErrorStatus(ErrorStatus::Error::KO));

    mGames.erase(game);
}

void GamesManager::disconnectHostFromHisEventualGameRunning(const std::string& host) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByUserAddressIp(host);

    if (game == mGames.end())
        return;

    (*game)->delUser(host);
}

/*
** PlayerCommunicationManager::OnPlayerCommunicationManagerEvent
*/ 
void GamesManager::onPlayerFire(const PlayerCommunicationManager &, const std::string &, int) {
}

void GamesManager::onPlayerMove(const PlayerCommunicationManager &, IResource::Direction, const std::string &, int) {
}

/*
** Game::OnGameEvent
*/
void GamesManager::onTerminatedGame(std::shared_ptr<Game>) {

}

void GamesManager::joinGame(const std::string &, const std::string &, const std::string &) {
}

void GamesManager::observeGame(const std::string &host, const std::string &/*name*/) {
    ScopedLock scopedLock(mMutex);

    disconnectHostFromHisEventualGameRunning(host);
}

void GamesManager::leaveGame(const std::string &host) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByUserAddressIp(host);

    if (game == mGames.end())
        throw GamesManagerException("Try to leave a player that he isn't on a game", ErrorStatus(ErrorStatus::Error::KO));

    (*game)->delUser(host);
}

void GamesManager::updatePseudo(const std::string &, const std::string &) {
}

const Game::GameProperties &GamesManager::getGameProperties(const std::string &name) const {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByName(name);

    if (game == mGames.end())
        throw GamesManagerException("Try to get properties of an undefined game", ErrorStatus(ErrorStatus::Error::KO));

    return (*game)->getProperties();
}

const std::list<Game::GameProperties> &GamesManager::getGamesProperties(void) const {
    ScopedLock scopedLock(mMutex);

    auto gamesProperties = new std::list<Game::GameProperties>{};

    for (const auto& game : mGames)
        gamesProperties->push_back(game->getProperties());

    return *gamesProperties;
}

std::vector<std::shared_ptr<Game>>::const_iterator GamesManager::findGameByName(const std::string& name) const {
    return std::find_if(mGames.begin(), mGames.end(), [&name](const std::shared_ptr<Game>& game) {
        return game.get()->getProperties().getName() == name;
    });
}

std::vector<std::shared_ptr<Game>>::const_iterator GamesManager::findGameByUserAddressIp(const std::string& addressIp) const {
    return std::find_if(mGames.begin(), mGames.end(), [&addressIp](const std::shared_ptr<Game>& game) {
        auto playersAddress = game.get()->getUsers();
        for (const auto& playerAddress : playersAddress) {
            if (playerAddress.second == addressIp)
                return true;
        }
        return false;
    });
}
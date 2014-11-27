#include "GamesManager.hpp"
#include "GamesManagerException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"

#include <algorithm>
#include <functional>
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
        *mThreadPool << std::bind(&Game::stateGame, game);
        *mThreadPool << std::bind(&Game::check, game);
        *mThreadPool << std::bind(&Game::update, game);
    }
}

void GamesManager::createGame(const Game::GameProperties& properties) {
    ScopedLock scopedLock(mMutex);

    auto game = std::shared_ptr<Game>{ std::make_shared<Game>(properties) };

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

/*
** PlayerCommunicationManager::OnPlayerCommunicationManagerEvent
*/ 
void GamesManager::onPlayerFire(const PlayerCommunicationManager &playerCommunicationManager, const std::string &host, int port) {
    try {
        ScopedLock scopedLock(mMutex);

        auto game = findGameByHost(host);

        if (game == mGames.end())
            throw GamesManagerException("Try to fire a player that is not in a game", ErrorStatus(ErrorStatus::Error::KO));
        
        // (*game)->fire(host);

        (void)playerCommunicationManager;
        (void)port;
        // faut créer sendCreateRessource ??
        //mPlayerCommunicationManager.sendCreateResource(host, port, id???)
    }
    catch (const GamesManagerException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GamesManager::onPlayerMove(const PlayerCommunicationManager &playerCommunicationManager, IResource::Direction direction, const std::string &host, int port) {
    try {
        ScopedLock scopedLock(mMutex);

        auto game = findGameByHost(host);

        if (game == mGames.end())
            throw GamesManagerException("Try to fire a player that is not in a game", ErrorStatus(ErrorStatus::Error::KO));

        (void)playerCommunicationManager;
        (void)direction;
        (void)port;
        //(*game)->move(host, direction);
        // auto component = getComponent(host);
        //mPlayerCommunicationManager.sendMoveResource(host, port, id ? ? , IResource::Type::PLAYER, component->getX(), component->getY(), component->getAngle());
    }
    catch (const GamesManagerException& e) {
        std::cerr << e.what() << std::endl;
    }
}

/*
** Game::OnGameEvent
*/
void GamesManager::onTerminatedGame(const std::shared_ptr<Game>& game) {
    auto users = game->getUsers();
    //std::for_each(users.begin(), users.end(), std::bind1st(std::mem_fun(&GamesManager::leaveGame), this));
    auto game_it = findGameByGamePtr(game);
    mGames.erase(game_it);
}

void GamesManager::joinGame(Game::USER_TYPE typeUser, const std::string &host, const std::string &name, const std::string &pseudo) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByName(name);

    if (game == mGames.end())
        throw GamesManagerException("Try to join an undefined game party name", ErrorStatus(ErrorStatus::Error::KO));

    leaveGame(host, false);
    (*game)->addUser(typeUser, host, pseudo);
}

void GamesManager::playGame(const std::string &host, const std::string &name, const std::string &pseudo) {
    joinGame(Game::USER_TYPE::PLAYER, host, name, pseudo);
}

void GamesManager::spectateGame(const std::string &host, const std::string &name, const std::string &pseudo) {
    joinGame(Game::USER_TYPE::SPECTATOR, host, name, pseudo);
}

void GamesManager::leaveGame(const std::string &host, bool throwExcept) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByHost(host);

    if (game == mGames.end())
    {
        if (throwExcept)
            throw GamesManagerException("Try to leave a player that he isn't on a game", ErrorStatus(ErrorStatus::Error::KO));
        else
            return;
    }   

    (*game)->delUser(host);
}

void GamesManager::updatePseudo(const std::string &host, const std::string &pseudo) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByHost(host);

    if (game == mGames.end())
        throw GamesManagerException("Try to leave a player that he isn't on a game", ErrorStatus(ErrorStatus::Error::KO));

    auto user = (*game)->findUserByHost(host);
    user->setPseudo(pseudo);

}

const Game::GameProperties &GamesManager::getGameProperties(const std::string &name) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByName(name);

    if (game == mGames.end())
        throw GamesManagerException("Try to get properties of an undefined game", ErrorStatus(ErrorStatus::Error::KO));

    return (*game)->getProperties();
}

const std::list<Game::GameProperties> &GamesManager::getGamesProperties(void) const {
    ScopedLock scopedLock(mMutex);

    auto gamesProperties = std::shared_ptr<std::list<Game::GameProperties>> { std::make_shared<std::list<Game::GameProperties>>() };

    for (const auto& game : mGames)
        gamesProperties->push_back(game->getProperties());

    return *gamesProperties;
}

std::vector<std::shared_ptr<Game>>::iterator GamesManager::findGameByGamePtr(const std::shared_ptr<Game>& target) {
    return std::find_if(mGames.begin(), mGames.end(), [&target](const std::shared_ptr<Game>& game) {
        return game.get() == target.get();
    });
}

std::vector<std::shared_ptr<Game>>::iterator GamesManager::findGameByName(const std::string& name) {
    return std::find_if(mGames.begin(), mGames.end(), [&name](const std::shared_ptr<Game>& game) {
        return game.get()->getProperties().getName() == name;
    });
}

std::vector<std::shared_ptr<Game>>::iterator GamesManager::findGameByHost(const std::string& host) {
    return std::find_if(mGames.begin(), mGames.end(), [&host](const std::shared_ptr<Game>& game) {
        auto playersAddress = game.get()->getUsers();
        for (const auto& playerAddress : playersAddress) {
            if (playerAddress.getHost() == host)
                return true;
        }
        return false;
    });
}
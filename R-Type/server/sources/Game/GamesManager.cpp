#include "GamesManager.hpp"
#include "GameException.hpp"
#include "GamesManagerException.hpp"
#include "GameProperties.hpp"
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
        *mThreadPool << std::bind(&NGame::Game::stateGame, game);
        *mThreadPool << std::bind(&NGame::Game::check, game);
        *mThreadPool << std::bind(&NGame::Game::update, game);
    }
}

void GamesManager::createGame(const NGame::Properties& properties, const Peer &peer) {
    ScopedLock scopedLock(mMutex);

    auto game = std::shared_ptr<NGame::Game>{ std::make_shared<NGame::Game>(properties) };

    game->setListener(this);
    game->setOwner(peer);

    mGames.push_back(game);
}

void GamesManager::removeGame(const Peer &peer, const std::string& name) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByName(name);

    if (game == mGames.end())
        throw GamesManagerException("Try to delete an undefined game", ErrorStatus(ErrorStatus::Error::KO));

    if (peer == (*game)->getOwner())
        mGames.erase(game);
    else
        throw GamesManagerException("You can remove a game only if you are owner", ErrorStatus(ErrorStatus::Error::KO));
}

/*
** PlayerCommunicationManager::OnPlayerCommunicationManagerEvent
*/ 
void GamesManager::onPlayerFire(const PlayerCommunicationManager &, const Peer &peer) {
    try {
        ScopedLock scopedLock(mMutex);

        auto game = findGameByHost(peer);

        if (game == mGames.end())
            throw GamesManagerException("Try to fire a player that is not in a game", ErrorStatus(ErrorStatus::Error::KO));
        
        (*game)->fire(peer);
        //mPlayerCommunicationManager.sendMoveResource()
    }
    catch (const GamesManagerException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GamesManager::onPlayerMove(const PlayerCommunicationManager &, IResource::Direction direction, const Peer &peer) {
    try {
        ScopedLock scopedLock(mMutex);

        auto game = findGameByHost(peer);

        if (game == mGames.end())
            throw GamesManagerException("Try to fire a player that is not in a game", ErrorStatus(ErrorStatus::Error::KO));

        (*game)->move(peer, direction);
        //mPlayerCommunicationManager.sendMoveResource()
    }
    catch (const GamesManagerException& e) {
        std::cerr << e.what() << std::endl;
    }
}

/*
** Game::OnGameEvent
*/
void GamesManager::onTerminatedGame(const std::string &name) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByName(name);

    if (game == mGames.end())
        throw GamesManagerException("Try to terminate an undefined game party name", ErrorStatus(ErrorStatus::Error::KO));

    auto users = (*game)->getUsers();
    std::for_each(users.begin(), users.end(), [&](const NGame::User& user) {
        const Peer& peer = user.getPeer();
        mPlayerCommunicationManager.removePeerFromWhiteList(peer);
    });
    mGames.erase(game);
}

void GamesManager::joinGame(NGame::USER_TYPE typeUser, const Peer &peer, const std::string &name, const std::string &pseudo) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByName(name);
    
    if (game == mGames.end())
       throw GamesManagerException("Try to join an undefined game party name", ErrorStatus(ErrorStatus::Error::KO));
    
    leaveGame(peer, false);
    (*game)->addUser(typeUser, peer, pseudo);
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

void GamesManager::leaveGame(const Peer &peer, bool throwExcept) {
    ScopedLock scopedLock(mMutex);

    try {
        auto game = findGameByHost(peer);
        if (game == mGames.end())
        {
            if (throwExcept)
                throw GamesManagerException("Try to leave a player that he isn't on a game", ErrorStatus(ErrorStatus::Error::KO));
            else
                return;
        }
        (*game)->delUser(peer);
        mPlayerCommunicationManager.removePeerFromWhiteList(peer);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::updatePseudo(const Peer &peer, const std::string &pseudo) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByHost(peer);

    if (game == mGames.end())
        throw GamesManagerException("Try to leave a player that he isn't on a game", ErrorStatus(ErrorStatus::Error::KO));

    try {
        auto user = (*game)->findUserByHost(peer);
        if (user == (*game)->getUsers().end())
            throw GameException("Try to delete an undefined address ip");
        user->setPseudo(pseudo);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

const NGame::Properties &GamesManager::getGameProperties(const std::string &name) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByName(name);

    if (game == mGames.end())
        throw GamesManagerException("Try to get properties of an undefined game", ErrorStatus(ErrorStatus::Error::KO));

    return (*game)->getProperties();
}

const std::list<NGame::Properties> &GamesManager::getGamesProperties(void) const {
    ScopedLock scopedLock(mMutex);

    auto gamesProperties = std::shared_ptr<std::list<NGame::Properties>> { std::make_shared<std::list<NGame::Properties>>() };

    for (const auto& game : mGames)
        gamesProperties->push_back(game->getProperties());

    return *gamesProperties;
}

std::vector<std::shared_ptr<NGame::Game>>::iterator GamesManager::findGameByName(const std::string& name) {
    return std::find_if(mGames.begin(), mGames.end(), [&name](const std::shared_ptr<NGame::Game>& game) {
        return game.get()->getProperties().getName() == name;
    });
}

std::vector<std::shared_ptr<NGame::Game>>::iterator GamesManager::findGameByHost(const Peer &peer) {
    return std::find_if(mGames.begin(), mGames.end(), [&peer](const std::shared_ptr<NGame::Game>& game) {
        auto playersAddress = game.get()->getUsers();
        for (const auto& playerAddress : playersAddress) {
            if (playerAddress.getPeer() == peer)
                return true;
        }
        return false;
    });
}

const ScriptLoader& GamesManager::getScriptLoader(void) const {
    return mScriptLoader;
}
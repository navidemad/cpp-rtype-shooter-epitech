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
    // beg test : create fake game
    /*
    Game::GameProperties properties;

    properties.setName("epitech game");
    properties.setLevelName("darkvador");
    properties.setNbPlayers(4);
    properties.setNbSpectators(6);

    createGame(properties, "127.0.0.1");
    */
    // end test

    for (;;) for (const auto &game : mGames) {
        *mThreadPool << std::bind(&Game::updatePositions, game);
        *mThreadPool << std::bind(&Game::checkRessources, game);
    }
}

void GamesManager::createGame(const Game::GameProperties& properties, const std::string& host) {
    ScopedLock scopedLock(mMutex);
    mGames.push_back(std::shared_ptr<Game>{ std::make_shared<Game>(properties, host) });
}

std::vector<std::shared_ptr<Game>>::iterator GamesManager::findGame(const std::string& name) {
    return std::find_if(mGames.begin(), mGames.end(), [&name](const std::shared_ptr<Game>& game) {
        return game.get()->getProperties().getName() == name;
    });
}

void GamesManager::removeGame(const std::string& name) {
    ScopedLock scopedLock(mMutex);

    auto game = findGame(name);

    if (game == mGames.end())
        throw GamesManagerException("Try to delete an undefined game");

    mGames.erase(game);
}

void GamesManager::onPlayerFire(const PlayerCommunicationManager &, const std::string &, int) {
}

void GamesManager::onPlayerMove(const PlayerCommunicationManager &, IResource::Direction, const std::string &, int) {
}

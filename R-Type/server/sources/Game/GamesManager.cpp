#include "GamesManager.hpp"
#include "GamesManagerException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"

#include <algorithm>
#include <iostream>

GamesManager::GamesManager(void) : mThreadPool(ThreadPool::getInstance()), mMutex(PortabilityBuilder::getMutex()) {

}

GamesManager::~GamesManager(void) {
    mGames.clear();
}

void GamesManager::run(void) {
    for (;;) for (const auto &game : mGames) {
        game->updatePositions();
        game->checkRessources();
    }
}

void GamesManager::createGame(const Game::GameProperties& properties) {
    ScopedLock scopedLock(mMutex);
    mGames.push_back(std::shared_ptr<Game>{ std::make_shared<Game>(properties) });
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

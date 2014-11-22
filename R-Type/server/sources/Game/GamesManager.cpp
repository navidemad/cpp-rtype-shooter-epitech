#include "GamesManager.hpp"

GamesManager::GamesManager(void) : mThreadPool(Utils::make_unique<ThreadPool>(6)) {

}

GamesManager::~GamesManager(void) {

}

void GamesManager::run(void) {

}

void GamesManager::createGame(const Game::GameProperties&) {

}

void GamesManager::removeGame(const std::string&) {

}
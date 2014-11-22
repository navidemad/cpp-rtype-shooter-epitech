#include "Game.hpp"

Game::Game(void) {

}

Game::~Game(void) {

}

void Game::updateTimer(void) {

}

void Game::updatePositions(void) {

}

void Game::checkRessources(void) {

}

void Game::addPlayer(void) {

}

void Game::delPlayer(void) {

}

void Game::terminateGame(void) {

}

Game::GameProperties::GameProperties(void) : mName(""), mLevelName(""), mNbPlayers(0), mNbSpectators(0) {
}

Game::GameProperties::~GameProperties(void) {

}

inline void Game::GameProperties::setName(const std::string& name) {
    mName = name;
}

inline void Game::GameProperties::setLevelName(const std::string& levelName) {
    mLevelName = levelName;
}

inline void Game::GameProperties::setNbPlayers(int nbPlayers) {
    mNbPlayers = nbPlayers;
}

inline void Game::GameProperties::setNbSpectators(int nbSpectators) {
    mNbSpectators = nbSpectators;
}


inline const std::string& Game::GameProperties::getName(void) const {
    return mName;
}

inline const std::string& Game::GameProperties::getLevelName(void) const {
    return mLevelName;
}

inline int Game::GameProperties::getNbPlayers(void) const {
    return mNbPlayers;
}

inline int Game::GameProperties::getNbSpectators(void) const {
    return mNbSpectators;
}

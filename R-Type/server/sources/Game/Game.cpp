#include "Game.hpp"

Game::Game(const Game::GameProperties& properties) : mProperties(properties) {

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

const Game::GameProperties& Game::getProperties(void) const {
    return mProperties;
}

Game::GameProperties::GameProperties(void) : mName(""), mLevelName(""), mNbPlayers(0), mNbSpectators(0) {
}

Game::GameProperties::~GameProperties(void) {

}

void Game::GameProperties::setName(const std::string& name) {
    mName = name;
}

void Game::GameProperties::setLevelName(const std::string& levelName) {
    mLevelName = levelName;
}

void Game::GameProperties::setNbPlayers(int nbPlayers) {
    mNbPlayers = nbPlayers;
}

void Game::GameProperties::setNbSpectators(int nbSpectators) {
    mNbSpectators = nbSpectators;
}


const std::string& Game::GameProperties::getName(void) const {
    return mName;
}

const std::string& Game::GameProperties::getLevelName(void) const {
    return mLevelName;
}

int Game::GameProperties::getNbPlayers(void) const {
    return mNbPlayers;
}

int Game::GameProperties::getNbSpectators(void) const {
    return mNbSpectators;
}

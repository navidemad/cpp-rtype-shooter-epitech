#include "Game.hpp"

Game::Game(const Game::GameProperties& properties, const std::string& hostOwner) : mProperties(properties), isRunning(true) {
    addPlayer(hostOwner);
}

Game::~Game(void) {

}

void Game::updatePositions(void) {

}

void Game::checkRessources(void) {

}

void Game::addPlayer(const std::string& ipAddress) {
    mPlayersAddress.push_back(ipAddress);
}

void Game::delPlayer(const std::string& ipAddress) {
    mPlayersAddress.remove_if([&ipAddress](const std::string& it) { return it == ipAddress; });
}

void Game::terminateGame(void) {
    isRunning = false;
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

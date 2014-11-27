#include "Game.hpp"
#include "GameException.hpp"
#include <algorithm>

Game::Game(const Game::GameProperties& properties, const std::string& hostOwner) : mListener(nullptr), mProperties(properties) {
    addUser(USER_TYPE::PLAYER, hostOwner);
}

void Game::setListener(Game::OnGameEvent *listener) {
    mListener = listener;
}

void Game::updatePositions(void) {

}

void Game::checkRessources(void) {

}

int Game::countUserByType(Game::USER_TYPE type) const {
    return std::count_if(mUsers.begin(), mUsers.end(), [&type](const std::pair<Game::USER_TYPE, std::string>& user) { return user.first == type; });
}

std::list<std::pair<Game::USER_TYPE, std::string>>::const_iterator Game::findUserByAddressIp(const std::string& addressIp) const {
    return std::find_if(mUsers.begin(), mUsers.end(), [&addressIp](const std::pair<Game::USER_TYPE, std::string>& user) { return user.second == addressIp; });
}

void Game::tryAddPlayer(Game::USER_TYPE type, const std::string& ipAddress) {
    if (mProperties.getNbPlayers() < mProperties.getMaxPlayers())
        throw GameException("No place for new players");

    mUsers.push_back(make_pair(type, ipAddress));
    mProperties.setNbPlayers(mProperties.getNbPlayers() + 1);
}

void Game::tryAddSpectator(Game::USER_TYPE type, const std::string& ipAddress) {
    if (mProperties.getNbSpectators() < mProperties.getMaxSpectators())
        throw GameException("No place for new spectators");

    mUsers.push_back(make_pair(type, ipAddress));
    mProperties.setNbSpectators(mProperties.getNbSpectators() + 1);
}

void Game::addUser(Game::USER_TYPE type, const std::string& ipAddress) {
    if (type == USER_TYPE::PLAYER)
        tryAddPlayer(type, ipAddress);
    else if (type == USER_TYPE::SPECTATOR)
        tryAddSpectator(type, ipAddress);
    else
        throw GameException("Invalid user type");
}

void Game::delUser(const std::string& ipAddress) {
    auto user = findUserByAddressIp(ipAddress);

    if (user == mUsers.end())
        throw GameException("Try to delete an undefined address ip");

    if ((*user).first == USER_TYPE::PLAYER)
        mProperties.setNbPlayers(mProperties.getNbPlayers() - 1);
    else if ((*user).first == USER_TYPE::SPECTATOR)
        mProperties.setNbPlayers(mProperties.getNbSpectators() - 1);

    mUsers.erase(user);
}

const std::list<std::pair<Game::USER_TYPE, std::string>>& Game::getUsers() const {
    return mUsers;
}

void Game::terminateGame(void) {
    if (mListener)
        mListener->onTerminatedGame(shared_from_this());
}

const Game::GameProperties& Game::getProperties(void) const {
    return mProperties;
}

/*
** nested class GameProperties
*/
Game::GameProperties::GameProperties(void) : mName(""), mLevelName(""), mNbPlayers(0), mNbMaxPlayers(0), mNbSpectators(0), mNbMaxSpectators(0) {
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

void Game::GameProperties::setNbMaxPlayers(int nbPlayers) {
    mNbMaxPlayers = nbPlayers;
}

void Game::GameProperties::setNbSpectators(int nbSpectators) {
    mNbSpectators = nbSpectators;
}

void Game::GameProperties::setNbMaxSpectators(int nbSpectators) {
    mNbMaxSpectators = nbSpectators;
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

int Game::GameProperties::getMaxPlayers(void) const {
    return mNbMaxPlayers;
}

int Game::GameProperties::getNbSpectators(void) const {
    return mNbSpectators;
}

int Game::GameProperties::getMaxSpectators(void) const {
    return mNbMaxSpectators;
}

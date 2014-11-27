#include "Game.hpp"
#include "GameException.hpp"
#include <algorithm>

Game::Game(const Game::GameProperties& properties) : mListener(nullptr), mProperties(properties), mIsRunning(false), mAlreadyRunOneTime(false) {
}

void Game::setListener(Game::OnGameEvent *listener) {
    mListener = listener;
}

#define X_MIN (0.0f)
#define X_MAX (640.0f)

#define Y_MIN (0.0f)
#define Y_MAX (480.0f)

void Game::checkStateGame(void) {
    /*
    ** le jeu doit pas se terminer si la partie a déjà été lancée, mais qu'il ne reste plus que de spectateurs
    */
    if (mAlreadyRunOneTime && !mIsRunning)
    {
        terminateGame();
    }
    else
    {
        mIsRunning = mProperties.getNbPlayers() > 0;
        if (mIsRunning)
            mAlreadyRunOneTime = true;
    }
}

void Game::killComponentOutOfScreen(void) {
    if (!mIsRunning)
        return;
    for (auto& component : mComponents)
    {
        if (component.getX() < X_MIN || component.getX() > X_MAX || component.getY() < Y_MIN || component.getX() > Y_MAX)
        {
            component.setLife(0);
            /*
            ** on devrait remove la component
            ** si c'est un type joueur, alors on switch le joueur en spectateur
            */
        }
    }
}

void Game::updatePositions(void) {
    if (!mIsRunning)
        return;
    for (auto& component : mComponents)
    {
        (void)component;
        /*
        ** changer la position en fonction du delta et de la vitesse (delta * speed) les setX et setY
        */
    }
}

void Game::checkRessources(void) {
    if (!mIsRunning)
        return;
}

int Game::countUserByType(Game::USER_TYPE type) const {
    return std::count_if(mUsers.begin(), mUsers.end(), [&type](const User& user) { return user.getType() == type; });
}

std::list<Game::User>::iterator Game::findUserByHost(const std::string& host) {
    return std::find_if(mUsers.begin(), mUsers.end(), [&host](const User& user) { return user.getHost() == host; });
}

void Game::tryAddPlayer(const User& user) {
    if (mProperties.getNbPlayers() < mProperties.getMaxPlayers())
        throw GameException("No place for new players");

    mUsers.push_back(user);

    mProperties.setNbPlayers(mProperties.getNbPlayers() + 1);
}

void Game::tryAddSpectator(const User& user) {
    if (mProperties.getNbSpectators() < mProperties.getMaxSpectators())
        throw GameException("No place for new spectators");

    mUsers.push_back(user);

    mProperties.setNbSpectators(mProperties.getNbSpectators() + 1);
}

void Game::addUser(Game::USER_TYPE type, const std::string& ipAddress, const std::string& pseudo) {
    if (type != USER_TYPE::PLAYER && type != USER_TYPE::SPECTATOR)
        throw GameException("Invalid user type");

    User user;

    user.setHost(ipAddress);
    user.setPseudo(pseudo);
    user.setType(type);

    if (type == USER_TYPE::PLAYER)
        tryAddPlayer(user);
    else if (type == USER_TYPE::SPECTATOR)
        tryAddSpectator(user);
}

void Game::delUser(const std::string& host) {
    auto user = findUserByHost(host);

    if (user == mUsers.end())
        throw GameException("Try to delete an undefined address ip");

    if ((*user).getType() == USER_TYPE::PLAYER)
        mProperties.setNbPlayers(mProperties.getNbPlayers() - 1);
    else if ((*user).getType() == USER_TYPE::SPECTATOR)
        mProperties.setNbPlayers(mProperties.getNbSpectators() - 1);

    mUsers.erase(user);
}

const std::list<Game::User>& Game::getUsers() const {
    return mUsers;
}

void Game::terminateGame(void) {
    if (mListener)
        mListener->onTerminatedGame(shared_from_this());
}

const Game::GameProperties& Game::getProperties(void) const {
    return mProperties;
}

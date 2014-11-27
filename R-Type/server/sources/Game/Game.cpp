#include "Game.hpp"
#include "GameException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include <algorithm>

const float Game::XMAX = 100.f;
const float Game::YMAX = 100.f;

Game::Game(const Game::GameProperties& properties) : mListener(nullptr), mProperties(properties), mIsRunning(false), mAlreadyRunOneTime(false), mMutex(PortabilityBuilder::getMutex()) {
}

void Game::setListener(Game::OnGameEvent *listener) {
    mListener = listener;
}

bool Game::outOfScreen(const Component& component) {
    bool eraseAsked = (component.getX() < 0.0f || component.getX() > Game::XMAX || component.getY() < 0.0f || component.getX() > Game::YMAX) != 0;
    if (eraseAsked)
    {
        auto user = findUserById(component.getId());
        if (user != mUsers.end())
            transferPlayerToSpectators(*user);
    }
    return (eraseAsked);
}

bool Game::collisionTouch(const Component& component, const Component& obstacle) const {
    if (&obstacle == &component)
        return false;

    float x = component.getX() - (component.getWidth() / 2);
    float y = component.getY() - (component.getHeight() / 2);
    float obsX = obstacle.getX() - (obstacle.getWidth() / 2);
    float obsY = obstacle.getY() - (obstacle.getHeight() / 2);

    return ((y + component.getHeight() > obsY && y < obsY + obstacle.getHeight()) &&
        (x + component.getWidth() > obsX && x < obsX + obstacle.getWidth()));
}

bool Game::collision(const Component& component) {
    for (const Component& obstacle : mComponents)
    {
        if (collisionTouch(component, obstacle))
        {

        }
    }
    return (false);
}

void Game::stateGame(void) {
    ScopedLock scopedLock(mMutex);

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

void Game::check(void) {
    ScopedLock scopedLock(mMutex);

    auto functionsCheck = std::vector<const std::function<bool(const Component&)>> 
    {
        std::bind(&Game::outOfScreen, this, std::placeholders::_1),
        std::bind(&Game::collision, this, std::placeholders::_1)
    };

    if (!mIsRunning)
        return;

    auto it_cur = mComponents.begin();
    auto it_end = mComponents.end();

    while (it_cur != it_end)
    {
        for (const auto& fct : functionsCheck)
        {
            if (fct(*it_cur))
                it_cur = mComponents.erase(it_cur);
            else
                ++it_cur;
        }
    }
}

void Game::update(void) {
    ScopedLock scopedLock(mMutex);

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

int Game::countUserByType(Game::USER_TYPE type) const {
    return std::count_if(mUsers.begin(), mUsers.end(), [&type](const User& user) { return user.getType() == type; });
}

std::vector<Game::User>::iterator Game::findUserByHost(const std::string& host) {
    return std::find_if(mUsers.begin(), mUsers.end(), [&host](const User& user) { return user.getHost() == host; });
}

std::vector<Game::User>::iterator Game::findUserById(uint64_t id) {
    return std::find_if(mUsers.begin(), mUsers.end(), [&id](const User& user) { return user.getId() == id; });
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
        mProperties.setNbSpectators(mProperties.getNbSpectators() - 1);

    mUsers.erase(user);
}

void Game::transferPlayerToSpectators(User& user) {
    mProperties.setNbPlayers(mProperties.getNbPlayers() - 1);
    mProperties.setNbSpectators(mProperties.getNbSpectators() + 1);
    user.setType(Game::USER_TYPE::SPECTATOR);
    //sendMessage that user die
}

const std::vector<Game::User>& Game::getUsers() const {
    return mUsers;
}

void Game::terminateGame(void) {
    if (mListener)
        mListener->onTerminatedGame(shared_from_this());
}

const Game::GameProperties& Game::getProperties(void) const {
    return mProperties;
}

#include "Game.hpp"
#include "GameException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include <algorithm>

const float NGame::Game::XMAX = 100.f;
const float NGame::Game::YMAX = 100.f;

NGame::Game::Game(const NGame::Properties& properties) :
mListener(nullptr), 
mProperties(properties), 
mIsRunning(false), 
mAlreadyRunOneTime(false), 
mMutex(PortabilityBuilder::getMutex())
{

}

void NGame::Game::setListener(NGame::Game::OnGameEvent *listener) {
    mListener = listener;
}

void NGame::Game::setOwner(const Peer& owner) {
    mOwner = owner;
}

const Peer& NGame::Game::getOwner(void) const {
    return mOwner;
}

bool NGame::Game::outOfScreen(const NGame::Component& component) {
    bool eraseAsked = (component.getX() < 0.0f || component.getX() > NGame::Game::XMAX || component.getY() < 0.0f || component.getX() > NGame::Game::YMAX) != 0;
    if (eraseAsked)
    {
        auto user = findUserById(component.getId());
        if (user != mUsers.end())
            transferPlayerToSpectators(*user);
    }
    return (eraseAsked);
}

bool NGame::Game::collisionTouch(const NGame::Component& component, const NGame::Component& obstacle) const {
    if (&obstacle == &component)
        return false;

    float x = component.getX() - (component.getWidth() / 2);
    float y = component.getY() - (component.getHeight() / 2);
    float obsX = obstacle.getX() - (obstacle.getWidth() / 2);
    float obsY = obstacle.getY() - (obstacle.getHeight() / 2);

    return ((y + component.getHeight() > obsY && y < obsY + obstacle.getHeight()) &&
        (x + component.getWidth() > obsX && x < obsX + obstacle.getWidth()));
}

bool NGame::Game::collisionWithBonus(const NGame::Component& /*component*/, const NGame::Component& /*obstacle*/) {
    // en fonction du bonus changer via les setters le component
    return false;
}

bool NGame::Game::collisionWithBullet(const NGame::Component& /*component*/, const NGame::Component& /*obstacle*/) {
    // retrait de vie // attention à pas enlever deux fois de la vie dans le cas bullet-player => -1, puis player-bullet => -1
    // attention aussi si la bullet vient d'un allié et non d'un monstre il faut pas retirer de vie
    // component.setLife(component->getLife() - 1);
    // notifier les utilisateurs qu'un allié a été touché
    return false;
}

bool NGame::Game::collisionWithMonster(const NGame::Component& /*component*/, const NGame::Component& /*obstacle*/) {
    // Mort instantané si on touche un monstre
    return true;
}

bool NGame::Game::collision(const NGame::Component& component) {

    static auto functionsHandleCollision = std::vector<std::function<bool(const NGame::Component&, const NGame::Component&)>>
    {
        std::bind(&NGame::Game::collisionWithBonus, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&NGame::Game::collisionWithBullet, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&NGame::Game::collisionWithMonster, this, std::placeholders::_1, std::placeholders::_2)
    };

    for (const NGame::Component& obstacle : mComponents)
        if (collisionTouch(component, obstacle))
            for (const auto& fct : functionsHandleCollision)
                if (fct(component, obstacle))
                    return true;

    return (false);
}

void NGame::Game::stateGame(void) {
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

void NGame::Game::check(void) {
    ScopedLock scopedLock(mMutex);

    static auto functionsCheck = std::vector<std::function<bool(const NGame::Component&)>>
    {
        std::bind(&NGame::Game::outOfScreen, this, std::placeholders::_1),
        std::bind(&NGame::Game::collision, this, std::placeholders::_1)
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

void NGame::Game::fire(const Peer&) {

}

void NGame::Game::move(const Peer&, IResource::Direction) {

}

void NGame::Game::update(void) {
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

int NGame::Game::countUserByType(NGame::USER_TYPE type) const {
    return std::count_if(mUsers.begin(), mUsers.end(), [&type](const NGame::User& user) { return user.getType() == type; });
}

std::vector<NGame::User>::iterator NGame::Game::findUserByHost(const Peer &peer) {
    return std::find_if(mUsers.begin(), mUsers.end(), [&](const NGame::User& user) { return user.getPeer() == peer; });
}

std::vector<NGame::User>::iterator NGame::Game::findUserById(uint64_t id) {
    return std::find_if(mUsers.begin(), mUsers.end(), [&id](const NGame::User& user) { return user.getId() == id; });
}

void NGame::Game::tryAddPlayer(const NGame::User& user) {
    if (mProperties.getNbPlayers() >= mProperties.getMaxPlayers())
        throw GameException("No place for new players");

    mUsers.push_back(user);

    mProperties.setNbPlayers(mProperties.getNbPlayers() + 1);
}

void NGame::Game::tryAddSpectator(const NGame::User& user) {
    if (mProperties.getNbSpectators() >= mProperties.getMaxSpectators())
        throw GameException("No place for new spectators");

    mUsers.push_back(user);

    mProperties.setNbSpectators(mProperties.getNbSpectators() + 1);
}

void NGame::Game::addUser(NGame::USER_TYPE type, const Peer &peer, const std::string& pseudo) {
    if (type != NGame::USER_TYPE::PLAYER && type != NGame::USER_TYPE::SPECTATOR)
        throw GameException("Invalid user type");

    NGame::User user;

    user.setPeer(peer);
    user.setPseudo(pseudo);
    user.setType(type);

    if (type == NGame::USER_TYPE::PLAYER)
        tryAddPlayer(user);
    else if (type == NGame::USER_TYPE::SPECTATOR)
        tryAddSpectator(user);
}

void NGame::Game::delUser(const Peer &peer) {
    auto user = findUserByHost(peer);

    if (user == mUsers.end())
        throw GameException("Try to delete an undefined address ip");

    if ((*user).getType() == NGame::USER_TYPE::PLAYER)
        mProperties.setNbPlayers(mProperties.getNbPlayers() - 1);
    else if ((*user).getType() == NGame::USER_TYPE::SPECTATOR)
        mProperties.setNbSpectators(mProperties.getNbSpectators() - 1);

    mUsers.erase(user);
}

void NGame::Game::transferPlayerToSpectators(NGame::User& user) {
    mProperties.setNbPlayers(mProperties.getNbPlayers() - 1);
    mProperties.setNbSpectators(mProperties.getNbSpectators() + 1);
    user.setType(NGame::USER_TYPE::SPECTATOR);
    // remove from peer list mPlayerCommunication
    //sendMessage that user die
}

const std::vector<NGame::User>& NGame::Game::getUsers() const {
    return mUsers;
}

void NGame::Game::terminateGame(void) {
    if (mListener)
        mListener->onTerminatedGame(mProperties.getName());
}

const NGame::Properties& NGame::Game::getProperties(void) const {
    return mProperties;
}

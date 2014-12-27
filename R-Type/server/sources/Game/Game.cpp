#include "Game.hpp"
#include "GameException.hpp"
#include "DynLibException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include "Utils.hpp"
#include "Script.hpp"
#include "Default.hpp"
#include "IScriptCommand.hpp"
#include <cmath>
#include <memory>
#include <algorithm>
#include <iostream>

const NGame::Game::tokenExec NGame::Game::tokenExecTab[] = {
    { IScriptCommand::Instruction::SPAWN, &NGame::Game::scriptCommandSpawn }
};

std::map<IResource::Type, std::string> NGame::Game::mDLLoader{
    { IResource::Type::PLAYER, "./../shared/resources/player/player" },
    { IResource::Type::CASTER, "./../shared/resources/caster/caster" },
    { IResource::Type::MELEE, "./../shared/resources/melee/melee" },
    { IResource::Type::SUPER, "./../shared/resources/super/super" },
    { IResource::Type::BULLET, "./../shared/resources/bullet/bullet" }
};

NGame::Game::Game(const NGame::Properties& properties, const std::shared_ptr<NGame::Script>& script) :
mProperties(properties),
mState(NGame::Game::State::NOT_STARTED),
mScript(std::make_shared<NGame::Script>(*script)),
mListener(nullptr),
mMutex(PortabilityBuilder::getMutex()),
mPullEnded(true),
mCurrentComponentMaxId(Config::Game::minIdComponent)
{
    std::cout << "Game stage_name: '" << mProperties.getLevelName() << "' created" << std::endl;
}

/*
** pull function called by threadPool
*/
void NGame::Game::pull(void) {
    setPullEnded(false);

    try {
        if (getState() == NGame::Game::State::RUNNING)
            broadcastMap();
        if (getState() == NGame::Game::State::RUNNING)
            resolvCollisions();
        if (getState() == NGame::Game::State::RUNNING)
            moveEntities();
        if (getState() == NGame::Game::State::RUNNING)
            fireEntities();
    }
    catch (const GameException& e) {
        Utils::logInfo(e.what());
        setState(NGame::Game::State::DONE);
    }

    setPullEnded(true);
}

void NGame::Game::broadcastMap(void) {
    ScopedLock scopedlock(mMutex);

    while (!(mScript->isFinish())) {
        const auto& currentCommand = mScript->currentCommand();
        if (getCurrentFrame() < currentCommand->getFrame())
            return;
        for (const auto& instr : tokenExecTab) {
            if (instr.commandCode == currentCommand->getInstruction()) {
                (this->*instr.fctPtr)(currentCommand);
                break;
            }
        }
        mScript->goToNextCommand();
    }
    mState = NGame::Game::State::DONE;
    logInfo("Level finished");
}

bool NGame::Game::outScreen(const std::shared_ptr<NGame::Component>& c1) const {
    return
        c1->getX() < 0 || c1->getX() > Config::Window::Width ||
        c1->getY() < 0 || c1->getY() > Config::Window::Height;
}

bool NGame::Game::handleCollisionBonus(const std::shared_ptr<NGame::Component>& c1, const std::shared_ptr<NGame::Component>&) {
    if (c1->getType() == IResource::Type::PLAYER) {
        c1->setLife(c1->getLife() * 2);
    }
    return false;
}

bool NGame::Game::handleCollisionBullet(const std::shared_ptr<NGame::Component>& c1, const std::shared_ptr<NGame::Component>& c2) {
    if (c1->getType() != IResource::Type::PLAYER &&
        c1->getType() != IResource::Type::CASTER &&
        c1->getType() != IResource::Type::MELEE &&
        c1->getType() != IResource::Type::SUPER)
        return false;

    if (c1->getType() == IResource::Type::PLAYER && c2->getOwner() != nullptr) {
        return false;
    }

    if (c1->getType() != IResource::Type::PLAYER && c2->getOwner() == nullptr) {
        return false;
    }

    c1->setLife(c1->getLife() - 1);

    bool stillAlive = c1->getLife() > 0;

    if (!stillAlive) {
        if (c1->getType() == IResource::Type::CASTER ||
            c1->getType() == IResource::Type::MELEE ||
            c1->getType() == IResource::Type::SUPER) {
            if (c2->getOwner() != nullptr) {
                c2->getOwner()->setScore(c2->getOwner()->getScore() + 10);
                if (mListener)
                    mListener->onNotifyUserGainScore(c2->getOwner()->getPeer(), c2->getOwner()->getId(), c2->getOwner()->getPseudo(), c2->getOwner()->getScore());
            }
        }
    }

    return stillAlive;
}

bool NGame::Game::handleCollisionPlayer(const std::shared_ptr<NGame::Component>&, const std::shared_ptr<NGame::Component>&) {
    return false;
}

bool NGame::Game::handleCollisionMonster(const std::shared_ptr<NGame::Component>& c1, const std::shared_ptr<NGame::Component>&) {
    return (c1->getType() == IResource::Type::PLAYER);
}

bool NGame::Game::handleCollision(const std::shared_ptr<NGame::Component>& c1, const std::shared_ptr<NGame::Component>& c2) {

    static std::map<IResource::Type, std::function<bool(const std::shared_ptr<NGame::Component>&, const std::shared_ptr<NGame::Component>&)>> handler
    {
        { IResource::Type::BONUS, std::bind(&NGame::Game::handleCollisionBonus, this, std::placeholders::_1, std::placeholders::_2) },
        { IResource::Type::BULLET, std::bind(&NGame::Game::handleCollisionBullet, this, std::placeholders::_1, std::placeholders::_2) },
        { IResource::Type::PLAYER, std::bind(&NGame::Game::handleCollisionPlayer, this, std::placeholders::_1, std::placeholders::_2) },
        { IResource::Type::CASTER, std::bind(&NGame::Game::handleCollisionMonster, this, std::placeholders::_1, std::placeholders::_2) },
        { IResource::Type::MELEE, std::bind(&NGame::Game::handleCollisionMonster, this, std::placeholders::_1, std::placeholders::_2) },
        { IResource::Type::SUPER, std::bind(&NGame::Game::handleCollisionMonster, this, std::placeholders::_1, std::placeholders::_2) },
};

    if (handler.find(c2->getType()) == handler.end()) {
        std::cout << "handleCollision with unknown type" << std::endl;
        return false;
    }

    return handler[c2->getType()](c1, c2);
}

bool NGame::Game::needRemove(const std::shared_ptr<NGame::Component>& c1) {
    if (outScreen(c1)) {
        return true;
    }

    for (auto c2 : mComponents) {
        if (c1->getId() == c2->getId())
            continue;
        if (c1->intersect(c2))
            return handleCollision(c1, c2);
    }

    return false;
}

void NGame::Game::resolvCollisions(void) {
    ScopedLock scopedlock(mMutex);

    for (auto it = mComponents.begin(); it != mComponents.end();)
    {
        if (needRemove(*it))
        {
            if ((*it)->getType() == IResource::Type::PLAYER)
                transferPlayerToSpectators((*it)->getOwner());
            if (mListener)
                mListener->onNotifyUsersComponentRemoved(mUsers, (*it)->getId());
            it = mComponents.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void NGame::Game::moveEntities(void) {
    ScopedLock scopedlock(mMutex);

    for (auto component : mComponents)
        if (component->getType() != IResource::Type::PLAYER && component->canMove())
            component->updatePositions();
}

void NGame::Game::fireEntities(void) {
    ScopedLock scopedlock(mMutex);

    for (std::vector<std::shared_ptr<NGame::Component>>::size_type i = 0, n = mComponents.size(); i < n; ++i) {
        if ((mComponents[i]->getType() == IResource::Type::CASTER || mComponents[i]->getType() == IResource::Type::SUPER) && mComponents[i]->canFire()) {
            //spawn("bullet", mComponents[i]->getX(), mComponents[i]->getY(), mComponents[i]->getAngle(), mComponents[i]->getOwner());
            //n = mComponents.size();
        }
    }
}

/*
** workflow internal game
*/
void NGame::Game::addComponentInList(const std::shared_ptr<NGame::Component>& component) {
    ScopedLock scopedlock(mMutex);

    mComponents.push_back(component);
}

void NGame::Game::addUserInList(const std::shared_ptr<NGame::User>& user) {
    ScopedLock scopedlock(mMutex);

    mUsers.push_back(user);
}

float NGame::Game::spawnX(void) const {
    return Config::Window::Width * 0.1f;
}

float NGame::Game::spawnY(void) const {
    return 200.f + mUsers.size() * 125.f;
}

void NGame::Game::addUser(NGame::USER_TYPE type, const Peer &peer, const std::string& pseudo) {
    if (type != NGame::USER_TYPE::PLAYER && type != NGame::USER_TYPE::SPECTATOR)
        throw GameException("Invalid user type");

    auto user = std::make_shared<NGame::User>();

    user->setPeer(peer);
    user->setPseudo(pseudo);
    user->setType(type);
    user->setScore(0);

    if (type == NGame::USER_TYPE::PLAYER) {
        if (getProperties().getNbPlayers() >= getProperties().getMaxPlayers())
            throw GameException("No place for new players");
        user->setId(getProperties().getNbPlayers() + 1);
        addUserInList(user);
        getProperties().setNbPlayers(getProperties().getNbPlayers() + 1);
        if (getState() == NGame::Game::State::NOT_STARTED) {
            initTimer();
            setState(NGame::Game::State::RUNNING);
        }
        {
            ScopedLock scopedlock(mMutex);
            spawn("player", spawnX(), spawnY(), Config::Game::angleTab[IResource::Direction::RIGHT], user);
            move(user->getPeer(), IResource::Direction::RIGHT);  // try patch display ship when new connection
        }
    }
    else if (type == NGame::USER_TYPE::SPECTATOR) {
        if (getProperties().getNbSpectators() >= getProperties().getMaxSpectators())
            throw GameException("No place for new spectators");
        user->setId(0);
        addUserInList(user);
        getProperties().setNbSpectators(getProperties().getNbSpectators() + 1);
    }

    auto listener = getListener();
    if (listener)
        listener->onNotifyTimeElapsedPing(peer, getCurrentFrame());
}

void NGame::Game::cleanComponents(const std::shared_ptr<NGame::User>& user) {
    for (auto it = mComponents.begin(); it != mComponents.end();)
        if ((*it)->getOwner().get() == user.get())
            it = mComponents.erase(it);
        else
            ++it;
}

void NGame::Game::delUser(const Peer &peer) {
    ScopedLock scopedlock(mMutex);
    auto user = findUserByHost(peer);
    if (user->getType() == NGame::USER_TYPE::PLAYER)
        mProperties.setNbPlayers(mProperties.getNbPlayers() - 1);
    else if (user->getType() == NGame::USER_TYPE::SPECTATOR)
        mProperties.setNbSpectators(mProperties.getNbSpectators() - 1);
    cleanComponents(user);
    mUsers.erase(std::remove(std::begin(mUsers), std::end(mUsers), user), std::end(mUsers));
}

void NGame::Game::transferPlayerToSpectators(std::shared_ptr<NGame::User>& user) {
    mProperties.setNbPlayers(mProperties.getNbPlayers() - 1);
    if (mListener)
        mListener->onRemovePeerFromWhiteList(user->getPeer());
    if (mProperties.getNbSpectators() >= mProperties.getMaxSpectators())
        throw GameException("No place for new spectators");
    user->setType(NGame::USER_TYPE::SPECTATOR);
    mUsers.push_back(user);
    mProperties.setNbSpectators(mProperties.getNbSpectators() + 1);
}

/*
** workflow gaming fire + move
*/

void NGame::Game::fire(const Peer &peer) {
    std::shared_ptr<NGame::Component> component_player;
    {
        ScopedLock scopedlock(mMutex);
        std::shared_ptr<NGame::User>& user = findUserByHost(peer);
        component_player = findComponentByUser(user);
        if (component_player->canFire())
            spawn("bullet", component_player->getX(), component_player->getY(), Config::Game::angleTab[IResource::Direction::RIGHT], user);
    }
}

void NGame::Game::move(const Peer &peer, IResource::Direction direction) {
    ScopedLock scopedlock(mMutex);
    auto component = findComponentByUser(findUserByHost(peer));
    component->setAngle(Config::Game::angleTab[direction]);
    component->updatePositions();
    if (mListener)
       mListener->onNotifyUsersComponentAdded(mUsers, component);
}

void    NGame::Game::spawn(const std::string& name, float x, float y, float angle, const std::shared_ptr<NGame::User>& owner) {
    for (const auto& path : mDLLoader) {
        if (name == Utils::basename(path.second)) {
            try {
                std::shared_ptr<NGame::Component> component = std::make_shared<NGame::Component>();

                component->getDynLib()->libraryLoad(path.second);
                void* entry_point = component->getDynLib()->functionLoad("entry_point");
                if (entry_point == nullptr)
                    throw DynLibException("entry_point function not found");
                IResource* resource = reinterpret_cast<IResource*(*)(void)>(entry_point)();
                if (!resource)
                    throw DynLibException("failed when trying to reinterpret_cast<IResource*>");

                component->setId(++mCurrentComponentMaxId);

                component->setX(x);
                component->setY(y);
                component->setAngle(angle);
                component->setOwner(owner);
                component->setResource(resource);

                component->setWidth(component->getResource()->getWidth());
                component->setHeight(component->getResource()->getHeight());
                component->setMoveSpeed(component->getResource()->getMoveSpeed());
                component->setFireDeltaTime(component->getResource()->getFireDeltaTime());
                component->setLife(component->getResource()->getLife());
                component->setType(component->getResource()->getType());

                mComponents.push_back(component);

                if (mListener)
                    mListener->onNotifyUsersComponentAdded(mUsers, component);

                return;
            }
            catch (const DynLibException& e) {
                throw GameException(e.what());
            }
        }
    }
    throw GameException("try to create an invalide entity name: " + name);
}

void	NGame::Game::scriptCommandSpawn(const IScriptCommand* command) {
    auto commandScriptSpawn = dynamic_cast<const ScriptSpawn*>(command);

    if (!commandScriptSpawn)
        throw GameException("dynamic_cast failed when try converting 'const IScriptCommand*' to 'const ScriptSpawn*'");

    spawn(commandScriptSpawn->getSpawnName(), commandScriptSpawn->getX(), commandScriptSpawn->getY(), commandScriptSpawn->getAngle(), nullptr);
}

/*
** getters
*/
NGame::Game::OnGameEvent* NGame::Game::getListener(void) const {
    return mListener;
}

float NGame::Game::getCurrentFrame(void) const {
    return static_cast<float>(mScriptTimer.getDelta()) / 1E6f;
}

NGame::Properties& NGame::Game::getProperties(void) {
    ScopedLock scopedlock(mMutex);

    return mProperties;
}

std::vector<std::shared_ptr<NGame::User>>& NGame::Game::getUsers(void) {
    ScopedLock scopedlock(mMutex);

    return mUsers;
}

NGame::Game::State NGame::Game::getState(void) const {
    ScopedLock scopedlock(mMutex);

    return mState;
}

const Peer& NGame::Game::getOwner(void) const {
    ScopedLock scopedlock(mMutex);

    return mOwner;
}

bool NGame::Game::getPullEnded(void) const {
    ScopedLock scopedlock(mMutex);

    return mPullEnded;
}

uint64_t NGame::Game::getCurrentComponentMaxId(void) const {
    ScopedLock scopedlock(mMutex);

    return mCurrentComponentMaxId;
}

/*
** setters
*/
void NGame::Game::setListener(NGame::Game::OnGameEvent* listener) {
    ScopedLock scopedlock(mMutex);

    mListener = listener;
}

void NGame::Game::setState(NGame::Game::State state) {
    ScopedLock scopedlock(mMutex);

    mState = state;
}

void NGame::Game::setOwner(const Peer& owner) {
    ScopedLock scopedlock(mMutex);

    mOwner = owner;
}

void NGame::Game::setPullEnded(bool pullEnded) {
    ScopedLock scopedlock(mMutex);

    mPullEnded = pullEnded;
}

void NGame::Game::setCurrentComponentMaxId(uint64_t currentComponentMaxId) {
    ScopedLock scopedlock(mMutex);

    mCurrentComponentMaxId = currentComponentMaxId;
}

/*
** utils
*/
void NGame::Game::logInfo(const std::string &log) const {
    std::stringstream ss;

    ss << Utils::RED << "[GAME]" << Utils::YELLOW << "[" << "]> " << Utils::WHITE << log;
    Utils::logInfo(ss.str());
}

void NGame::Game::initTimer(void) {
    ScopedLock scopedlock(mMutex);;

    mScriptTimer.restart();
}

/*
** workflow STL
*/
std::shared_ptr<NGame::User>& NGame::Game::findUserByHost(const Peer &peer) {
    std::vector<std::shared_ptr<NGame::User>>::iterator it = std::find_if(mUsers.begin(), mUsers.end(), [&](const std::shared_ptr<NGame::User>& user) { return user->getPeer() == peer; });
    if (it == mUsers.end())
        throw GameException("user not found for this peer");

    return *it;
}

std::shared_ptr<NGame::User>& NGame::Game::findUserById(uint64_t id) {
    std::vector<std::shared_ptr<NGame::User>>::iterator it = std::find_if(mUsers.begin(), mUsers.end(), [&id](const std::shared_ptr<NGame::User>& user) {
        return user->getId() == id;
    });
    if (it == mUsers.end())
        throw GameException("user not found for this id");

    return *it;
}

std::shared_ptr<NGame::Component>& NGame::Game::findComponentById(uint64_t id) {
    std::vector<std::shared_ptr<NGame::Component>>::iterator it = std::find_if(mComponents.begin(), mComponents.end(), [&id](const std::shared_ptr<NGame::Component>& component) { return component->getId() == id; });
    if (it == mComponents.end())
        throw GameException("component not found for component.getId() = '" + Utils::toString<uint64_t>(id) +"'");

    return *it;
}

std::shared_ptr<NGame::Component>& NGame::Game::findComponentByUser(const std::shared_ptr<NGame::User>& user) {
    std::vector<std::shared_ptr<NGame::Component>>::iterator it = std::find_if(mComponents.begin(), mComponents.end(), [&user](const std::shared_ptr<NGame::Component>& component) {
        return component->getOwner().get() == user.get();
    });
    if (it == mComponents.end())
        throw GameException("component not found for finding by user");

    return *it;
}

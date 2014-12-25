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
            checkCollisions();
        if (getState() == NGame::Game::State::RUNNING)
            moveEntities();
    }
    catch (const GameException& e) {
        Utils::logInfo(e.what());
        setState(NGame::Game::State::DONE);
    }

    setPullEnded(true);
}

void NGame::Game::broadcastMap(void) {
    while (!(getScript()->isFinish())) {
        const auto& currentCommand = getScript()->currentCommand();
        if (getCurrentFrame() < currentCommand->getFrame())
            return;
        for (const auto& instr : tokenExecTab) {
            if (instr.commandCode == currentCommand->getInstruction()) {
                (this->*instr.fctPtr)(currentCommand);
                break;
            }
        }
        getScript()->goToNextCommand();
    }
    setState(NGame::Game::State::DONE);
    logInfo("Level finished");
}

void NGame::Game::checkCollisions(void) {
    return;
    /*
    auto components = getComponents();
    for (auto it = components.begin(); it != components.end();) {
    if (collision(*it))
    {
    if ((*it).getType() == IResource::Type::PLAYER) // exception quand on spam SPACE
    {
    try {
    NGame::User& user = findUserById((*it).getId());
    transferPlayerToSpectators(user);
    }
    catch (const GameException&) {}
    }
    auto listener = getListener();
    if (listener)
    listener->onNotifyUsersComponentRemoved(getUsers(), (*it).getId());
    it = components.erase(it);
    }
    else
    ++it;
    }
    */
}

void NGame::Game::moveEntities(void) {
    Scopedlock(mMutex);

    for (auto component : mComponents)
    {
        if (component->canMove())
        {
            if (component->getType() == IResource::Type::PLAYER)
            {
                if (component->wantMove())
                {
                    component->setAngle(component->angleMove());
                    component->subMove();
                    updatePositionComponent(component);
                }
            }
            else
            {
                updatePositionComponent(component);
            }
        }
    }
}

/*
** workflow internal game
*/
void NGame::Game::addComponentInList(const std::shared_ptr<NGame::Component>& component) {
    Scopedlock(mMutex);

    mComponents.push_back(component);
}

void NGame::Game::addUserInList(const std::shared_ptr<NGame::User>& user) {
    Scopedlock(mMutex);

    mUsers.push_back(user);
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
        double spawnX = 1.;
        double spawnY = Config::Window::yMax / (1 + user->getId()); // a revoir
        spawn("player", spawnX, spawnY, Config::Game::angleTab[IResource::Direction::RIGHT], user->getId());
    }
    else if (type == NGame::USER_TYPE::SPECTATOR) {
        if (getProperties().getNbSpectators() >= getProperties().getMaxSpectators())
            throw GameException("No place for new spectators");
        user->setId(0); // checker car risuqe de match avec les types USER_TYPE::PLAYER
        addUserInList(user);
        getProperties().setNbSpectators(getProperties().getNbSpectators() + 1);
    }

    auto listener = getListener();
    if (listener)
        listener->onNotifyTimeElapsedPing(peer, getCurrentFrame());
}

void NGame::Game::delUser(const Peer &peer) {
    NGame::USER_TYPE type;
    {
        Scopedlock(mMutex);
        std::vector<std::shared_ptr<NGame::User>>::iterator user = findIteratorUserByHost(peer);
        if (user == mUsers.end())
            throw GameException("Try to delete an undefined address ip");
        type = (*user)->getType();
        mUsers.erase(user);
    }

    if (type == NGame::USER_TYPE::PLAYER)
        getProperties().setNbPlayers(getProperties().getNbPlayers() - 1);
    else if (type == NGame::USER_TYPE::SPECTATOR)
        getProperties().setNbSpectators(getProperties().getNbSpectators() - 1);
}

void NGame::Game::transferPlayerToSpectators(std::shared_ptr<NGame::User>& user) {
    getProperties().setNbPlayers(getProperties().getNbPlayers() - 1);
    auto listener = getListener();
    if (listener)
        listener->onRemovePeerFromWhiteList(user->getPeer());
    if (getProperties().getNbSpectators() >= getProperties().getMaxSpectators())
        throw GameException("No place for new spectators"); // checker que faire si plus de place
    user->setType(NGame::USER_TYPE::SPECTATOR);
    addUserInList(user);
    getProperties().setNbSpectators(getProperties().getNbSpectators() + 1);
}

void NGame::Game::updatePositionComponent(std::shared_ptr<NGame::Component>& component) {

    double pi = 3.14159265358979323846;
    double angleInRad = component->getAngle() * pi / 180;
    double speed = component->getMoveSpeed();
    double dx = speed * cos(angleInRad);
    double dy = speed * sin(angleInRad);

    component->setX(component->getX() + dx);
    component->setY(component->getY() + dy);

    if (mListener)
        mListener->onNotifyUsersComponentAdded(mUsers, component);
}

/*
** workflow gaming fire + move
*/

void NGame::Game::fire(const Peer &peer) {
    std::shared_ptr<NGame::Component> component_player;
    {
        Scopedlock(mMutex);
        std::shared_ptr<NGame::User>& user = findUserByHost(peer);
        component_player = findComponentByOwnerId(user->getId());
    }
    spawn("bullet", component_player->getX(), component_player->getY(), Config::Game::angleTab[IResource::Direction::RIGHT], component_player->getId());
}

void NGame::Game::move(const Peer &peer, IResource::Direction direction) {
    Scopedlock(mMutex);
    findComponentByOwnerId(findUserByHost(peer)->getId())->addMove(Config::Game::angleTab[direction]);
}

void    NGame::Game::spawn(const std::string& name, double x, double y, short angle, uint64_t ownerId) {
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

                setCurrentComponentMaxId(getCurrentComponentMaxId() + 1);

                component->setId(getCurrentComponentMaxId());

                component->setX(x);
                component->setY(y);
                component->setAngle(angle);
                component->setOwnerId(ownerId);
                component->setResource(resource);

                component->setWidth(component->getResource()->getWidth());
                component->setHeight(component->getResource()->getHeight());
                component->setMoveSpeed(component->getResource()->getMoveSpeed());
                component->setLife(component->getResource()->getLife());
                component->setType(component->getResource()->getType());
                
                addComponentInList(component);

                auto listener = getListener();
                if (listener)
                    listener->onNotifyUsersComponentAdded(getUsers(), component);

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

    spawn(commandScriptSpawn->getSpawnName(), commandScriptSpawn->getX(), commandScriptSpawn->getY(), commandScriptSpawn->getAngle(), 0);
}























































































































































































































































































/*
** getters
*/
std::shared_ptr<NGame::Script>& NGame::Game::getScript(void) {
    Scopedlock(mMutex);

    return mScript;
}

NGame::Game::OnGameEvent* NGame::Game::getListener(void) {
    return mListener;
}

double NGame::Game::getCurrentFrame(void) {
    Scopedlock(mMutex);

    return (static_cast<double>(std::clock() - mTimer) / static_cast<double>(CLOCKS_PER_SEC));
}

NGame::Properties& NGame::Game::getProperties(void) {
    Scopedlock(mMutex);

    return mProperties;
}

std::vector<std::shared_ptr<NGame::User>>& NGame::Game::getUsers(void) {
    Scopedlock(mMutex);

    return mUsers;
}

NGame::Game::State NGame::Game::getState(void) const {
    Scopedlock(mMutex);

    return mState;
}

const Peer& NGame::Game::getOwner(void) {
    Scopedlock(mMutex);

    return mOwner;
}

bool NGame::Game::getPullEnded(void) {
    Scopedlock(mMutex);

    return mPullEnded;
}

uint64_t NGame::Game::getCurrentComponentMaxId(void) {
    Scopedlock(mMutex);

    return mCurrentComponentMaxId;
}

/*
** setters
*/
void NGame::Game::setListener(NGame::Game::OnGameEvent* listener) {
    Scopedlock(mMutex);

    mListener = listener;
}

void NGame::Game::setState(NGame::Game::State state) {
    Scopedlock(mMutex);

    mState = state;
}

void NGame::Game::setOwner(const Peer& owner) {
    Scopedlock(mMutex);

    mOwner = owner;
}

void NGame::Game::setPullEnded(bool pullEnded) {
    Scopedlock(mMutex);

    mPullEnded = pullEnded;
}

void NGame::Game::setCurrentComponentMaxId(uint64_t currentComponentMaxId) {
    Scopedlock(mMutex);

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
    Scopedlock(mMutex);

    mTimer = std::clock();
}

/*
** workflow STL
*/
std::vector<std::shared_ptr<NGame::User>>::iterator NGame::Game::findIteratorUserByHost(const Peer &peer) {
    return std::find_if(mUsers.begin(), mUsers.end(), [&](const std::shared_ptr<NGame::User>& user) { return user->getPeer() == peer; });
}

std::shared_ptr<NGame::User>& NGame::Game::findUserByHost(const Peer &peer) {
    std::vector<std::shared_ptr<NGame::User>>::iterator it = std::find_if(mUsers.begin(), mUsers.end(), [&](const std::shared_ptr<NGame::User>& user) { return user->getPeer() == peer; });
    if (it == mUsers.end())
        throw GameException("user not found for this peer");

    return *it;
}

std::shared_ptr<NGame::User>& NGame::Game::findUserById(uint64_t id) {
    std::vector<std::shared_ptr<NGame::User>>::iterator it = std::find_if(mUsers.begin(), mUsers.end(), [&id](const std::shared_ptr<NGame::User>& user) { return user->getId() == id; });
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

std::shared_ptr<NGame::Component>& NGame::Game::findComponentByOwnerId(uint64_t ownerId) {
    std::vector<std::shared_ptr<NGame::Component>>::iterator it = std::find_if(mComponents.begin(), mComponents.end(), [&ownerId](const std::shared_ptr<NGame::Component>& component) {
        //std::cout << "component.getOwnerId(): '" << component.getOwnerId() << "' and ownerId: '" << ownerId << "'" << std::endl;
        return component->getOwnerId() == ownerId;
    });
    if (it == mComponents.end())
        throw GameException("component not found for component.getOwnerId() = '" + Utils::toString<uint64_t>(ownerId) +"'");

    return *it;
}

/*
** check :: collision
*/
bool NGame::Game::collision(std::shared_ptr<NGame::Component>& /*component*/) {
    return true;

    /*
    static const auto& functionsHandleCollision = std::vector<std::function<bool(std::shared_ptr<NGame::Component>&, std::shared_ptr<NGame::Component>&)>>
    {
    std::bind(&NGame::Game::collisionWithNoLife, this, std::placeholders::_1),
    std::bind(&NGame::Game::collisionWithBonus, this, std::placeholders::_1, std::placeholders::_2),
    std::bind(&NGame::Game::collisionWithBullet, this, std::placeholders::_1, std::placeholders::_2),
    std::bind(&NGame::Game::collisionWithEnnemy, this, std::placeholders::_1, std::placeholders::_2)
    };

    auto& components = getComponents();
    for (auto& obstacle : components) {
    if (collisionTouch(component, obstacle)) {
    return true; // a debugger below

    std::cout << "collisionTouch = true" << std::endl;
    int i;
    i = 1;
    for (const auto& fct : functionsHandleCollision) {
    std::cout << "functionsHandleCollision #" << i++ << std::endl;
    if (fct(component, obstacle)) {
    std::cout << "functionsHandleCollision return true" << std::endl;
    return true;
    }
    std::cout << "functionsHandleCollision return false" << std::endl;
    }
    }
    }
    return false;
    */
}

bool NGame::Game::collisionTouch(const std::shared_ptr<NGame::Component>& component, const std::shared_ptr<NGame::Component>& obstacle) const {
    if (&obstacle == &component)
        return false;

    if (component->getX() < Config::Window::xMin || component->getX() > Config::Window::xMax || component->getY() < Config::Window::yMin || component->getX() > Config::Window::yMax)
    {
        std::cout << "####### ID: '" << component->getId() << "' OUT OF SCREEN ########" << std::endl;
        return true;
    }

    return false; // a debugger below
    double x = component->getX() - component->getWidth() / 2.; // probleme car getWidth est en px et getX en ratio %
    double y = component->getY() - component->getHeight() / 2.;
    double obsX = obstacle->getX() - obstacle->getWidth() / 2.;
    double obsY = obstacle->getY() - obstacle->getHeight() / 2.;

    return (
        (y + component->getHeight() > obsY && y < obsY + obstacle->getHeight())
        &&
        (x + component->getWidth() > obsX && x < obsX + obstacle->getWidth())
        );
}

bool NGame::Game::collisionWithNoLife(std::shared_ptr<NGame::Component>&) {
    return true;
}

bool NGame::Game::collisionWithBonus(std::shared_ptr<NGame::Component>& component, std::shared_ptr<NGame::Component>& obstacle) {
    if (obstacle->getType() == IResource::Type::PLAYER && component->getType() == IResource::Type::BONUS) {
        component->setLife(component->getLife() * 2); // les bonus double votre nombre de vie (à changer par la vitesse ou par le nombre de boulettes)
        return true;
    }
    return false;
}

bool NGame::Game::collisionWithBullet(std::shared_ptr<NGame::Component>& component, std::shared_ptr<NGame::Component>& obstacle) {
    if (obstacle->getType() == IResource::Type::BULLET)
    {
        bool friendBullet = false;
        try {
            findUserById(obstacle->getId());
            friendBullet = true;
        }
        catch (const GameException&) {}
        switch (component->getType())
        {
        case IResource::Type::PLAYER:
            if (friendBullet)
                return false;
            component->setLife(component->getLife() - 1);
            return component->getLife() == 0;
        default:
            break;
        }
    }
    return false;
}

bool NGame::Game::collisionWithEnnemy(std::shared_ptr<NGame::Component>& /*component*/, std::shared_ptr<NGame::Component>& /*obstacle*/) {
    return false;
    /*
    if (obstacle->getType() == IResource::Type::CASTER)
    {
    const auto& user = findUserById(component->getId());
    bool friendBullet = user != getUsers().end();
    switch (component->getType())
    {
    case IResource::Type::PLAYER:
    // contact direct player avec monstre => mort instané du player
    return true;
    case IResource::Type::BULLET:
    // bullet d'un joueur qui touche un monstre
    if (friendBullet)
    {
    user->setScore(user->getScore() + 1);
    auto listener = getListener();
    if (listener)
    listener->onNotifyUserGainScore(user->getPeer(), user->getId(), user->getPseudo(), user->getScore());
    component->setLife(component->getLife() - 1);
    return component->getLife() == 0;
    }
    default:
    break;
    }
    }
    return false;
    */
}


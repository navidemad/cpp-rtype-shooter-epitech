#include "Game.hpp"
#include "GameException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include "Utils.hpp"
#include "Script.hpp"
#include <algorithm>
#include <iostream>

const NGame::Game::tokenExec NGame::Game::tokenExecTab[] = {
	{ IScriptCommand::Instruction::NAME, &NGame::Game::recvName },
	{ IScriptCommand::Instruction::REQUIRE, &NGame::Game::recvRequire },
	{ IScriptCommand::Instruction::ACTION, &NGame::Game::recvAction },
	{ IScriptCommand::Instruction::ADD_CRON, &NGame::Game::recvAddCron },
	{ IScriptCommand::Instruction::REMOVE_CRON, &NGame::Game::recvRemoveCron }
};

const float NGame::Game::XMAX = 100.f;
const float NGame::Game::YMAX = 100.f;

NGame::Game::Game(const NGame::Properties& properties, const Script& script) :
mScript(script),
mListener(nullptr),
mProperties(properties),
mState(NGame::Game::State::NOT_STARTED), 
mMutex(PortabilityBuilder::getMutex()),
mIsThreadRunning(false)
{
}

/*
** pull function called by threadPool
*/
void NGame::Game::pull(void) {
    ScopedLock scopedLock(mMutex);

	mIsThreadRunning = false;
	double FRAME_PER_SEC = 60.0;
	double start_time = mTimer.frame();
	double delta_time;
	do {
		actions(); // script loading
		check(); // check collisions
		update(); // update positions
		delta_time = mTimer.frame() - start_time;
	} while (delta_time < 1 / FRAME_PER_SEC);
	mIsThreadRunning = false;
}

void NGame::Game::actions(void) {
    ScopedLock scopedLock(mMutex);

    double currentFrame = mTimer.frame();

    static auto it = mScript.getCommands().begin();
    static auto it_end = mScript.getCommands().end();

    while (it != it_end)
    {
		auto scriptCommand = (*it);
		if (scriptCommand->getFrame() > currentFrame)
            return;
        for (const auto &instr : tokenExecTab) {
            if (instr.commandCode == scriptCommand->getInstruction())
			{
                (this->*instr.fctPtr)();
                break;
            }
        }
        ++it;
    }
    mState = NGame::Game::State::DONE;
	logInfo("Level finished");
}

void NGame::Game::check(void) {
    ScopedLock scopedLock(mMutex);

    static auto functionsCheck = std::vector<std::function<bool(const NGame::Component&)>>
    {
        std::bind(&NGame::Game::outOfScreen, this, std::placeholders::_1),
        std::bind(&NGame::Game::collision, this, std::placeholders::_1)
    };

    auto it_cur = mComponents.begin();
    auto it_end = mComponents.end();

    while (it_cur != it_end)
    {
        for (const auto& fct : functionsCheck)
        {
            if (fct(*it_cur))
            {
                // deleteRessource
                it_cur = mComponents.erase(it_cur);
            }
            else
                ++it_cur;
        }
    }
}

void NGame::Game::update(void) {
    ScopedLock scopedLock(mMutex);
}

/*
** getters
*/
NGame::Game::State NGame::Game::getState(void) const {
    return mState;
}

const Peer& NGame::Game::getOwner(void) const {
    return mOwner;
}

const std::vector<NGame::User>& NGame::Game::getUsers() const {
    return mUsers;
}

const NGame::Properties& NGame::Game::getProperties(void) const {
    return mProperties;
}

bool NGame::Game::isThreadRunning(void) const {
	return mIsThreadRunning;
}

/*
** setters
*/
void NGame::Game::setListener(NGame::Game::OnGameEvent *listener) {
    mListener = listener;
}

void NGame::Game::setOwner(const Peer& owner) {
    mOwner = owner;
}

/*
** utils
*/
void NGame::Game::logInfo(const std::string &log) {
	std::stringstream ss;

	ss << Utils::RED << "[GAME]" << Utils::YELLOW << "[" << "]> " << Utils::WHITE << log;
	Utils::logInfo(ss.str());
}

/*
** check :: outOfScreen
*/
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

/*
** check :: collision
*/
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

/*
** workflow STL
*/
int NGame::Game::countUserByType(NGame::USER_TYPE type) const {
    return std::count_if(mUsers.begin(), mUsers.end(), [&type](const NGame::User& user) { return user.getType() == type; });
}

std::vector<NGame::User>::iterator NGame::Game::findUserByHost(const Peer &peer) {
    return std::find_if(mUsers.begin(), mUsers.end(), [&](const NGame::User& user) { return user.getPeer() == peer; });
}

std::vector<NGame::User>::iterator NGame::Game::findUserById(uint64_t id) {
    return std::find_if(mUsers.begin(), mUsers.end(), [&id](const NGame::User& user) { return user.getId() == id; });
}

/*
** workflow internal game
*/
void NGame::Game::tryAddPlayer(const NGame::User& user) {
    if (mProperties.getNbPlayers() >= mProperties.getMaxPlayers())
        throw GameException("No place for new players");

    mUsers.push_back(user);

    mProperties.setNbPlayers(mProperties.getNbPlayers() + 1);
    mState = NGame::Game::State::RUNNING;
}

void NGame::Game::tryDelPlayer(void) {
	mProperties.setNbPlayers(mProperties.getNbPlayers() - 1);
	if (mProperties.getNbPlayers() == 0)
	{
		logInfo("tryDelPlayer > mProperties.getNbPlayers() == 0");
		mState = NGame::Game::State::DONE;
	}
}

void NGame::Game::tryAddSpectator(const NGame::User& user) {
    if (mProperties.getNbSpectators() >= mProperties.getMaxSpectators())
        throw GameException("No place for new spectators");

    mUsers.push_back(user);

    mProperties.setNbSpectators(mProperties.getNbSpectators() + 1);
}

void NGame::Game::tryDelSpectator(void) {
	mProperties.setNbSpectators(mProperties.getNbSpectators() - 1);
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
		tryDelPlayer();
    else if ((*user).getType() == NGame::USER_TYPE::SPECTATOR)
		tryDelSpectator();

    mUsers.erase(user);
}

void NGame::Game::transferPlayerToSpectators(NGame::User& user) {
	tryDelPlayer();
	tryAddPlayer(user);
	user.setType(NGame::USER_TYPE::SPECTATOR);
    // remove from peer list mPlayerCommunication
    //sendMessage that user die
}

/*
** workflow gaming fire + move
*/
void NGame::Game::fire(const Peer&) {

}

void NGame::Game::move(const Peer&, IResource::Direction) {

}

/*
** workflow scripts actions
*/
void	NGame::Game::recvName(void) {
	logInfo(__FUNCTION__);
}

void	NGame::Game::recvRequire(void) {
	logInfo(__FUNCTION__);
}

void	NGame::Game::recvAction(void) {
	logInfo(__FUNCTION__);
}

void	NGame::Game::recvAddCron(void) {
	logInfo(__FUNCTION__);
}

void	NGame::Game::recvRemoveCron(void) {
	logInfo(__FUNCTION__);
}

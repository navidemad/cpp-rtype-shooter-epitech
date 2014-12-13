#include "Game.hpp"
#include "GameException.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include "Utils.hpp"
#include "Script.hpp"
#include "ScriptName.hpp"
#include "ScriptRequire.hpp"
#include "ScriptAction.hpp"
#include "ScriptAddCron.hpp"
#include "ScriptRemoveCron.hpp"
#include <cmath>
#include <memory>
#include <algorithm>
#include <iostream>
#include <map>

const NGame::Game::tokenExec NGame::Game::tokenExecTab[] = {
	{ IScriptCommand::Instruction::NAME, &NGame::Game::scriptCommandName },
	{ IScriptCommand::Instruction::REQUIRE, &NGame::Game::scriptCommandRequire },
	{ IScriptCommand::Instruction::ACTION, &NGame::Game::scriptCommandAction },
	{ IScriptCommand::Instruction::ADD_CRON, &NGame::Game::scriptCommandAddCron },
	{ IScriptCommand::Instruction::REMOVE_CRON, &NGame::Game::scriptCommandRemoveCron }
};

const NGame::Game::tokenAngle NGame::Game::tokenAngleTab[] = {
	{ IResource::Direction::RIGHT, 0 },
	{ IResource::Direction::TOP, 90 },
	{ IResource::Direction::LEFT, 180 },
	{ IResource::Direction::BOTTOM, 270 }
};

const double NGame::Game::XMAX = 100.;
const double NGame::Game::YMAX = 100.;
const double NGame::Game::FRAMES_PER_SEC = 60.;
const uint64_t NGame::Game::START_ID_COMPONENT = 6;

NGame::Game::Game(const NGame::Properties& properties, const Script& script) :
mScript(script),
mListener(nullptr),
mProperties(properties),
mState(NGame::Game::State::NOT_STARTED),
mMutex(PortabilityBuilder::getMutex()),
mPullEnded(true),
mCurrentComponentMaxId(NGame::Game::START_ID_COMPONENT)
{
}

/*
** pull function called by threadPool
*/
void NGame::Game::pull(void) {
	ScopedLock scopedLock(mMutex);

	mPullEnded = false;

	if (mState == NGame::Game::State::RUNNING)
		actions();
	if (mState == NGame::Game::State::RUNNING)
		check();
	if (mState == NGame::Game::State::RUNNING)
		update();
	if (mTimer.ping())
		cronSendPingToSyncronizeClientTimer();

	mPullEnded = true;
}

void NGame::Game::actions(void) {
	std::shared_ptr<IScriptCommand> currentCommand;

	if (mScript.getCommands().size()) 
	{
		do
		{
			currentCommand = mScript.currentAction();

			if (mTimer.frame() < currentCommand->getFrame())
				return;

			for (const auto &instr : tokenExecTab)
			{
				if (instr.commandCode == currentCommand->getInstruction())
				{
					(this->*instr.fctPtr)(currentCommand);
					break;
				}
			}

		} while (mScript.goToNextAction());
	}
	mState = NGame::Game::State::DONE;
	logInfo("Level finished");
}

void NGame::Game::check(void) {
	for (auto it = mComponents.begin(); it != mComponents.end();) {
		if (collision(*it))
		{
			if (mListener)
				mListener->onNotifyUsersComponentRemoved(getUsers(), (*it).getId());
			it = mComponents.erase(it);
		}
		else
			++it;
	}
}

void NGame::Game::update(void) {
	for (auto& component : mComponents)
		if (component.getType() != IResource::Type::PLAYER)
			updatePositionComponent(component);
}

/*
** getters
*/
NGame::Game::State NGame::Game::getState(void) const {
    ScopedLock scopedLock(mMutex);

	return mState;
}

uint64_t NGame::Game::getCurrentComponentMaxId(void) const {
	ScopedLock scopedLock(mMutex);

	return mCurrentComponentMaxId;
}

const Peer& NGame::Game::getOwner(void) const {
    ScopedLock scopedLock(mMutex);

	return mOwner;
}

const std::vector<NGame::User>& NGame::Game::getUsers() const {
    ScopedLock scopedLock(mMutex);

	return mUsers;
}

const NGame::Properties& NGame::Game::getProperties(void) const {
    ScopedLock scopedLock(mMutex);

	return mProperties;
}

bool NGame::Game::pullEnded(void) const {
    ScopedLock scopedLock(mMutex);

	return mPullEnded;
}

void NGame::Game::setPullEnded(bool pullEnded) {
    ScopedLock scopedLock(mMutex);

	mPullEnded = pullEnded;
}

/*
** setters
*/
void NGame::Game::setListener(NGame::Game::OnGameEvent *listener) {
	mListener = listener;
}

void NGame::Game::setOwner(const Peer& owner) {
    ScopedLock scopedLock(mMutex);

	mOwner = owner;
}

/*
** utils
*/
void NGame::Game::logInfo(const std::string &log) const {
	std::stringstream ss;

	ss << Utils::RED << "[GAME]" << Utils::YELLOW << "[" << "]> " << Utils::WHITE << log;
	Utils::logInfo(ss.str());
}

/*
** check :: collision
*/
bool NGame::Game::collision(NGame::Component& component) {
	static auto functionsHandleCollision = std::vector<std::function<bool(NGame::Component&, NGame::Component&)>>
	{
		std::bind(&NGame::Game::collisionWithNoLife, this, std::placeholders::_1),
		std::bind(&NGame::Game::collisionWithBorders, this, std::placeholders::_1),
		std::bind(&NGame::Game::collisionWithBonus, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&NGame::Game::collisionWithBullet, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&NGame::Game::collisionWithEnnemy, this, std::placeholders::_1, std::placeholders::_2)
	};

	for (NGame::Component& obstacle : mComponents) {
		if (collisionTouch(component, obstacle)) {
			for (const auto& fct : functionsHandleCollision) {
				if (fct(component, obstacle)) {
					return true;
				}
			}
		}
	}
	return (false);
}

bool NGame::Game::collisionTouch(const NGame::Component& component, const NGame::Component& obstacle) const {
	if (&obstacle == &component)
		return false;

	if (component.getX() < 0.0f || component.getX() > NGame::Game::XMAX || component.getY() < 0.0f || component.getX() > NGame::Game::YMAX)
		return true;

	double x = component.getX() - component.getWidth() / 2.;
	double y = component.getY() - component.getHeight() / 2.;
	double obsX = obstacle.getX() - obstacle.getWidth() / 2.;
	double obsY = obstacle.getY() - obstacle.getHeight() / 2.;

	return ((y + component.getHeight() > obsY && y < obsY + obstacle.getHeight()) &&
		(x + component.getWidth() > obsX && x < obsX + obstacle.getWidth()));
}

bool NGame::Game::collisionWithNoLife(NGame::Component& component) {
	return findUserById(component.getId()) != mUsers.end() && component.getLife() == 0;
}

bool NGame::Game::collisionWithBorders(NGame::Component& component) {
	auto user = findUserById(component.getId());
	if (user != mUsers.end())
		transferPlayerToSpectators(*user);
	return true;
}

bool NGame::Game::collisionWithBonus(NGame::Component& component, NGame::Component& obstacle) {
	if (obstacle.getType() == IResource::Type::PLAYER && component.getType() == IResource::Type::BONUS) {
		component.setLife(component.getLife() * 2); // les bonus double votre nombre de vie (à changer par la vitesse ou par le nombre de boulettes)
		return true;
	}
	return false;
}

bool NGame::Game::collisionWithBullet(NGame::Component& component, NGame::Component& obstacle) {
	if (obstacle.getType() == IResource::Type::BULLET)
	{
		auto user = findUserById(obstacle.getId());
		bool friendBullet = user != mUsers.end();
		switch (component.getType())
		{
		case IResource::Type::PLAYER:
			if (friendBullet)
				return false;
			component.setLife(component.getLife() - 1);
			return component.getLife() == 0;
		default:
			break;
		}
	}
	return false;
}

bool NGame::Game::collisionWithEnnemy(NGame::Component& component, NGame::Component& obstacle) {
	if (obstacle.getType() == IResource::Type::ENNEMY)
	{
		auto user = findUserById(component.getId());
		bool friendBullet = user != mUsers.end();
		switch (component.getType())
		{
		case IResource::Type::PLAYER:
			// contact direct player avec monstre => mort instané du player
			return true;
		case IResource::Type::BULLET:
			// bullet d'un joueur qui touche un monstre
			if (friendBullet)
			{
				user->setScore(user->getScore() + 1);
				if (mListener)
					mListener->onNotifyUserGainScore(user->getPeer(), user->getId(), user->getPseudo(), user->getScore());
				component.setLife(component.getLife() - 1);
				return component.getLife() == 0;
			}
		default:
			break;
		}
	}
	return false;
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

std::vector<NGame::Component>::iterator NGame::Game::findComponentById(uint64_t id) {
	return std::find_if(mComponents.begin(), mComponents.end(), [&id](const NGame::Component& component) { return component.getId() == id; });
}

/*
** workflow internal game
*/
void NGame::Game::cronSendPingToSyncronizeClientTimer(void) const {
	if (mListener)
		for (const auto &user : getUsers())
			mListener->onNotifyTimeElapsedPing(user.getPeer(), mTimer.frame());
}

void NGame::Game::tryAddPlayer(NGame::User& user) {
	if (mProperties.getNbPlayers() >= mProperties.getMaxPlayers())
		throw GameException("No place for new players");

	NGame::Component component;

	double playerWidth = 32.;
	double playerHeight = 32.;
	double playerSpeed = 0.05;
	short playerAngle = 0;

	component.setX(1.);
	component.setY(NGame::Game::YMAX / 2.);
	component.setWidth(playerWidth);
	component.setHeight(playerHeight);
	component.setAngle(playerAngle);
	component.setSpeed(playerSpeed);
	component.setLife(10);
	component.setType(IResource::Type::PLAYER);
	component.setId(++mCurrentComponentMaxId);

	mComponents.push_back(component);

	user.setId(mCurrentComponentMaxId);
	mUsers.push_back(user);

	mProperties.setNbPlayers(mProperties.getNbPlayers() + 1);
	mState = NGame::Game::State::RUNNING;
}

void NGame::Game::tryDelPlayer(void) {
	mProperties.setNbPlayers(mProperties.getNbPlayers() - 1);
	if (mProperties.getNbPlayers() == 0)
	{
		logInfo("Game finished because nbPlayer reached 0");
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
    ScopedLock scopedLock(mMutex);

	if (type != NGame::USER_TYPE::PLAYER && type != NGame::USER_TYPE::SPECTATOR)
		throw GameException("Invalid user type");

	NGame::User user;

	user.setPeer(peer);
	user.setPseudo(pseudo);
	user.setType(type);
	user.setId(0);
	user.setScore(0);

	if (type == NGame::USER_TYPE::PLAYER)
		tryAddPlayer(user);
	else if (type == NGame::USER_TYPE::SPECTATOR)
		tryAddSpectator(user);
}

void NGame::Game::delUser(const Peer &peer) {
    ScopedLock scopedLock(mMutex);

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
	if (mListener)
		mListener->onRemovePeerFromWhiteList(user.getPeer());
}

void NGame::Game::updatePositionComponent(NGame::Component& component) {
	double newX = component.getX() + cos(component.getAngle()) * component.getSpeed(); // gestion du * deltaTime
	double newY = component.getY() + sin(component.getAngle()) * component.getSpeed(); // gestion du * deltaTime

	component.setX(newX);
	component.setY(newY);
}

/*
** workflow gaming fire + move
*/

NGame::Component NGame::Game::fire(const Peer &peer) {
	ScopedLock scopedLock(mMutex);
	NGame::Component component;
	
	double bulletWidth = 32.;
	double bulletHeight = 32.;
	double bulletSpeed = 0.05;
	short bulletAngle = 0;
	
	auto user = findUserByHost(peer);
	if (user == mUsers.end())
		throw GameException("fire a player that not in this game");
	auto component_user = findComponentById((*user).getId());
	if (component_user == mComponents.end())
		throw GameException("component_user that not in this game");

	component.setX((*component_user).getX());
	component.setY((*component_user).getY());
	component.setWidth(bulletWidth);
	component.setHeight(bulletHeight);
	component.setAngle(bulletAngle);
	component.setSpeed(bulletSpeed);
	component.setLife(0);
	component.setType(IResource::Type::BULLET);
	component.setId(++mCurrentComponentMaxId);

	mComponents.push_back(component);
		
	return component;
}

const NGame::Component& NGame::Game::move(const Peer &peer, IResource::Direction direction) {
	ScopedLock scopedLock(mMutex);

	auto user = findUserByHost(peer);
	if (user == mUsers.end())
		throw GameException("fire a player that not in this game");
	auto component = findComponentById((*user).getId());
	if (component == mComponents.end())
		throw GameException("component_user that not in this game");

	for (const auto &instr : tokenAngleTab)
	{
		if (instr.directionCode == direction)
		{
			(*component).setAngle(instr.angle);
			break;
		}
	}
	updatePositionComponent(*component);

	return *component;
}

/*
** workflow scripts actions
*/
void	NGame::Game::scriptCommandName(const std::shared_ptr<IScriptCommand> &command) {
	const std::shared_ptr<ScriptName> commandScriptName = std::static_pointer_cast<ScriptName>(command);
	
	// PAS SUR DE CA
	//if (commandScriptName->getName() != mProperties.getLevelName())
	//	throw GameException("script name request doesn't match with the level name of current game");

    std::cout << commandScriptName << std::endl;
}

void	NGame::Game::scriptCommandRequire(const std::shared_ptr<IScriptCommand> &command) {
    const std::shared_ptr<ScriptRequire> commandScriptRequire = std::static_pointer_cast<ScriptRequire>(command);

	// CHECK SI LA LIBRARIE .so / .dll EST PRESENTE DANS NOTRE STD::VECTOR<DynRessource> mRessources
	// if (mRessources.count(commandScriptRequire->getRessourceName()) == 0)
	//    throw GameException("script require ressource request doesn't match with game's ressources");
	
    std::cout << commandScriptRequire << std::endl;
}

void	NGame::Game::scriptCommandAction(const std::shared_ptr<IScriptCommand> &command) {
    const std::shared_ptr<ScriptAction> commandScriptAction = std::static_pointer_cast<ScriptAction>(command);

	// TODO
	// moveMob
	// spawnMob

    std::cout << commandScriptAction << std::endl;
}

void	NGame::Game::scriptCommandAddCron(const std::shared_ptr<IScriptCommand> &command) {
    const std::shared_ptr<ScriptAddCron> commandScriptAddCron = std::static_pointer_cast<ScriptAddCron>(command);

	// TODO
	// add cron task for a component

    std::cout << commandScriptAddCron << std::endl;
}

void	NGame::Game::scriptCommandRemoveCron(const std::shared_ptr<IScriptCommand> &command) {
    const std::shared_ptr<ScriptRemoveCron> commandScriptRemoveCron = std::static_pointer_cast<ScriptRemoveCron>(command);

	// TODO
	// remove cron task for a component

    std::cout << commandScriptRemoveCron << std::endl;
}

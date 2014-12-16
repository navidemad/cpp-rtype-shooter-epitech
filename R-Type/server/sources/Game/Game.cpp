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
	{ IResource::Direction::BOTTOM, 90 },
	{ IResource::Direction::LEFT, 180 },
	{ IResource::Direction::TOP, 270 }
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
	setPullEnded(false);

	try {
		if (getState() == NGame::Game::State::RUNNING)
			actions();
		if (getState() == NGame::Game::State::RUNNING)
			check();
		if (getState() == NGame::Game::State::RUNNING)
			update();
		if (getTimer().ping())
			cronSendPingToSyncronizeClientTimer();
	}
	catch (const GameException& e) {
		Utils::logError(e.what());
		setState(NGame::Game::State::DONE);
	}

	setPullEnded(true);
}

void NGame::Game::actions(void) {
	std::shared_ptr<IScriptCommand> currentCommand;

	///if (mTimer.frame() < 40.)
	//	return;
	if (getScript().getCommands().size()) 
	{
		do
		{
			currentCommand = getScript().currentAction();

			if (getTimer().frame() < currentCommand->getFrame()) // who is'nt in a game - exception en fin de partie
				return;

			for (const auto &instr : tokenExecTab)
			{
				if (instr.commandCode == currentCommand->getInstruction())
				{
					(this->*instr.fctPtr)(currentCommand);
					break;
				}
			}

		} while (getScript().goToNextAction());
	}
	setState(NGame::Game::State::DONE);
	logInfo("Level finished");
}

void NGame::Game::check(void) {
	auto& components = getComponents();
	for (auto it = components.begin(); it != components.end();) {
		if (collision(*it))
		{
			auto& users = getUsers();
			if ((*it).getType() == IResource::Type::PLAYER)
			{
				auto user = findUserById((*it).getId());
				if (user != users.end())
				{
					transferPlayerToSpectators(*user);
				}
			}
			auto listener = getListener();
		    if (listener)
		    	listener->onNotifyUsersComponentRemoved(users, (*it).getId());
			it = components.erase(it);
		}
		else
			++it;
	}
}

void NGame::Game::update(void) {
	auto& components = getComponents();
	for (auto& component : components) {
		if (component.getType() != IResource::Type::PLAYER) {
			updatePositionComponent(component);
			auto listener = getListener();
			if (listener)
		    	listener->onNotifyUsersComponentAdded(getUsers(), component);
		}
	}
}

/*
** getters
*/
Script& NGame::Game::getScript(void) {
	Scopedlock(getMutex());

	return mScript;
}

NGame::Game::OnGameEvent* NGame::Game::getListener(void) {
	Scopedlock(getMutex());

	return mListener;
}

Timer& NGame::Game::getTimer(void) {
	Scopedlock(getMutex());

	return mTimer;
}

NGame::Properties& NGame::Game::getProperties(void) {
	Scopedlock(getMutex());

	return mProperties;
}

std::vector<NGame::User>& NGame::Game::getUsers(void) {
	Scopedlock(getMutex());

	return mUsers;
}

std::vector<NGame::Component>& NGame::Game::getComponents(void) {
	Scopedlock(getMutex());

	return mComponents;
}

NGame::Game::State NGame::Game::getState(void) {
	Scopedlock(getMutex());

	return mState;
}

std::shared_ptr<IMutex>& NGame::Game::getMutex(void) {
	return mMutex;
}

Peer& NGame::Game::getOwner(void) {
	Scopedlock(getMutex());

	return mOwner;
}

bool NGame::Game::getPullEnded(void) {
	Scopedlock(getMutex());

	return mPullEnded;
}

uint64_t NGame::Game::getCurrentComponentMaxId(void) {
	Scopedlock(getMutex());

	return mCurrentComponentMaxId;
}

/*
** setters
*/
void NGame::Game::setScript(Script& script) {
	Scopedlock(getMutex());

	mScript = script;
}

void NGame::Game::setListener(NGame::Game::OnGameEvent* listener) {
	Scopedlock(getMutex());

	mListener = listener;
}

void NGame::Game::setProperties(NGame::Properties& properties) {
	Scopedlock(getMutex());

	mProperties = properties;
}

void NGame::Game::setUsers(std::vector<NGame::User>& users) {
	Scopedlock(getMutex());

	mUsers = users;
}

void NGame::Game::setComponents(std::vector<NGame::Component>& components) {
	Scopedlock(getMutex());

	mComponents = components;
}

void NGame::Game::setState(NGame::Game::State state) {
	Scopedlock(getMutex());

	mState = state;
}

void NGame::Game::setMutex(std::shared_ptr<IMutex>& mutex) {
	mMutex = mutex;
}

void NGame::Game::setOwner(const Peer& owner) {
	Scopedlock(getMutex());

	mOwner = owner;
}

void NGame::Game::setPullEnded(bool pullEnded) {
	Scopedlock(getMutex());

	mPullEnded = pullEnded;
}

void NGame::Game::setCurrentComponentMaxId(uint64_t currentComponentMaxId) {
	Scopedlock(getMutex());

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

/*
** check :: collision
*/
bool NGame::Game::collision(NGame::Component& component) {
	static auto functionsHandleCollision = std::vector<std::function<bool(NGame::Component&, NGame::Component&)>>
	{
		std::bind(&NGame::Game::collisionWithNoLife, this, std::placeholders::_1),
		std::bind(&NGame::Game::collisionWithBonus, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&NGame::Game::collisionWithBullet, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&NGame::Game::collisionWithEnnemy, this, std::placeholders::_1, std::placeholders::_2)
	};

	auto& components = getComponents();
	for (NGame::Component& obstacle : components) {
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
	return (false);
}

bool NGame::Game::collisionTouch(const NGame::Component& component, const NGame::Component& obstacle) const {
	if (&obstacle == &component)
		return false;

	if (component.getX() < 0.0f || component.getX() > NGame::Game::XMAX || component.getY() < 0.0f || component.getX() > NGame::Game::YMAX)
	{
		std::cout << "####### OUT OF SCREEN ########" << std::endl;
		return true;
	}

	return false; // a debugger below
	double x = component.getX() - component.getWidth() / 2.; // probleme car getWidth est en px et getX en ratio %
	double y = component.getY() - component.getHeight() / 2.;
	double obsX = obstacle.getX() - obstacle.getWidth() / 2.;
	double obsY = obstacle.getY() - obstacle.getHeight() / 2.;

	return (
		(y + component.getHeight() > obsY && y < obsY + obstacle.getHeight()) 
			&&
		(x + component.getWidth() > obsX && x < obsX + obstacle.getWidth())
		);
}

bool NGame::Game::collisionWithNoLife(NGame::Component& component) {
	return findUserById(component.getId()) != getUsers().end() && component.getLife() == 0;
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
		bool friendBullet = user != getUsers().end();
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
		bool friendBullet = user != getUsers().end();
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
				auto listener = getListener();
		    	if (listener)
		    		listener->onNotifyUserGainScore(user->getPeer(), user->getId(), user->getPseudo(), user->getScore());
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
int NGame::Game::countUserByType(NGame::USER_TYPE type) {
	return std::count_if(getUsers().begin(), getUsers().end(), [&type](const NGame::User& user) { return user.getType() == type; });
}

std::vector<NGame::User>::iterator NGame::Game::findUserByHost(const Peer &peer) {
	return std::find_if(getUsers().begin(), getUsers().end(), [&](const NGame::User& user) { return user.getPeer() == peer; });
}

std::vector<NGame::User>::iterator NGame::Game::findUserById(uint64_t id) {
	return std::find_if(getUsers().begin(), getUsers().end(), [&id](const NGame::User& user) { return user.getId() == id; });
}

std::vector<NGame::Component>::iterator NGame::Game::findComponentById(uint64_t id) {
	return std::find_if(getComponents().begin(), getComponents().end(), [&id](const NGame::Component& component) { return component.getId() == id; });
}

/*
** workflow internal game
*/
void NGame::Game::cronSendPingToSyncronizeClientTimer(void) {
	auto listener = getListener();
	if (listener) {
		auto& users = getUsers();
		for (const auto &user : users)
			listener->onNotifyTimeElapsedPing(user.getPeer(), getTimer().frame());
	}
}

void NGame::Game::addComponentInList(const NGame::Component& component) {
	Scopedlock(getMutex());

	mComponents.push_back(component);
}

void NGame::Game::addUserInList(const NGame::User& user) {
	Scopedlock(getMutex());

	mUsers.push_back(user);
}

void NGame::Game::eraseUserOfList(std::vector<NGame::User>::iterator& it) {
	Scopedlock(getMutex());

	mUsers.erase(it);
}

void NGame::Game::tryAddPlayer(NGame::User& user) {
	if (getProperties().getNbPlayers() >= getProperties().getMaxPlayers())
		throw GameException("No place for new players");

	NGame::Component component;

	double playerWidth = 32.;
	double playerHeight = 32.;
	double playerSpeed = 0.45;
	short playerAngle = 0;

	setCurrentComponentMaxId(getCurrentComponentMaxId() + 1);

	component.setX(1.);
	component.setY(NGame::Game::YMAX / 2.);
	component.setWidth(playerWidth);
	component.setHeight(playerHeight);
	component.setAngle(playerAngle);
	component.setSpeed(playerSpeed);
	component.setLife(10);
	component.setType(IResource::Type::PLAYER);
	component.setId(getCurrentComponentMaxId());

	addComponentInList(component);
	user.setId(getCurrentComponentMaxId());
	addUserInList(user);

	getProperties().setNbPlayers(getProperties().getNbPlayers() + 1);

    auto listener = getListener();
    if (listener)
    	listener->onNotifyUsersComponentAdded(getUsers(), component);

	setState(NGame::Game::State::RUNNING);
}

void NGame::Game::tryDelPlayer(void) {
	getProperties().setNbPlayers(getProperties().getNbPlayers() - 1);
	if (getProperties().getNbPlayers() == 0)
	{
		logInfo("Game finished because nbPlayer reached 0");
		setState(NGame::Game::State::DONE);
	}
}

void NGame::Game::tryAddSpectator(const NGame::User& user) {
	if (getProperties().getNbSpectators() >= getProperties().getMaxSpectators())
		throw GameException("No place for new spectators");

	addUserInList(user);
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
	user.setId(0);
	user.setScore(0);

	if (type == NGame::USER_TYPE::PLAYER)
		tryAddPlayer(user);
	else if (type == NGame::USER_TYPE::SPECTATOR)
		tryAddSpectator(user);
}

void NGame::Game::delUser(const Peer &peer) {
	auto user = findUserByHost(peer);

	if (user == getUsers().end())
		throw GameException("Try to delete an undefined address ip");

	if ((*user).getType() == NGame::USER_TYPE::PLAYER)
		tryDelPlayer();
	else if ((*user).getType() == NGame::USER_TYPE::SPECTATOR)
		tryDelSpectator();

	eraseUserOfList(user);
}

void NGame::Game::transferPlayerToSpectators(NGame::User& user) {
	auto listener = getListener();
    if (listener)
    	listener->onRemovePeerFromWhiteList(user.getPeer());
	tryDelPlayer();
	user.setType(NGame::USER_TYPE::SPECTATOR);
	tryAddSpectator(user);
}

void NGame::Game::updatePositionComponent(NGame::Component& component) {
	double angleInRad = component.getAngle() * M_PI / 180;
	double speed = component.getSpeed();
	double dx = speed * cos(angleInRad);
	double dy = speed * sin(angleInRad);

	component.setX(component.getX() + dx);
	component.setY(component.getY() + dy);
}

/*
** workflow gaming fire + move
*/

NGame::Component NGame::Game::fire(const Peer &peer) {
	NGame::Component component;
	
	double bulletWidth = 32.;
	double bulletHeight = 32.;
	double bulletSpeed = 0.0016;
	short bulletAngle = 0;
	
	auto user = findUserByHost(peer);
	if (user == getUsers().end())
		throw GameException("fire a player that not in this game");
	auto component_user = findComponentById((*user).getId());
	if (component_user == getComponents().end())
		throw GameException("NGame::Game::fire component_user that not in this game");

	component.setX((*component_user).getX());
	component.setY((*component_user).getY());
	component.setWidth(bulletWidth);
	component.setHeight(bulletHeight);
	component.setAngle(bulletAngle);
	component.setSpeed(bulletSpeed);
	component.setLife(0);
	component.setType(IResource::Type::BULLET);
	component.setId(++mCurrentComponentMaxId);

	addComponentInList(component);

	return component;
}

const NGame::Component& NGame::Game::move(const Peer &peer, IResource::Direction direction) {
	auto user = findUserByHost(peer);
	if (user == getUsers().end())
		throw GameException("fire a player that not in this game");
	auto component = findComponentById((*user).getId());
	if (component == getComponents().end())
		throw GameException("NGame::Game::move component_user that not in this game");

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
	logInfo(__FUNCTION__);
	const std::shared_ptr<ScriptName> commandScriptName = std::static_pointer_cast<ScriptName>(command);

	if (commandScriptName->getName() != getProperties().getLevelName())
		throw GameException("script name request doesn't match with the level name of current game");

    std::cout << commandScriptName << std::endl;
}

void	NGame::Game::scriptCommandRequire(const std::shared_ptr<IScriptCommand> &command) {
	logInfo(__FUNCTION__);
    const std::shared_ptr<ScriptRequire> commandScriptRequire = std::static_pointer_cast<ScriptRequire>(command);

	// CHECK SI LA LIBRARIE .so / .dll EST PRESENTE DANS NOTRE STD::VECTOR<DynRessource> mRessources
	// if (mRessources.count(commandScriptRequire->getRessourceName()) == 0)
	//    throw GameException("script require ressource request doesn't match with game's ressources");
	
    //std::cout << commandScriptRequire << std::endl;
}

void	NGame::Game::scriptCommandAction(const std::shared_ptr<IScriptCommand> &command) {
	logInfo(__FUNCTION__);
    const std::shared_ptr<ScriptAction> commandScriptAction = std::static_pointer_cast<ScriptAction>(command);

	// TODO
	// moveMob
	// spawnMob

    //std::cout << commandScriptAction << std::endl;
}

void	NGame::Game::scriptCommandAddCron(const std::shared_ptr<IScriptCommand> &command) {
	logInfo(__FUNCTION__);
    const std::shared_ptr<ScriptAddCron> commandScriptAddCron = std::static_pointer_cast<ScriptAddCron>(command);

	// TODO
	// add cron task for a component

    //std::cout << commandScriptAddCron << std::endl;
}

void	NGame::Game::scriptCommandRemoveCron(const std::shared_ptr<IScriptCommand> &command) {
	logInfo(__FUNCTION__);
    const std::shared_ptr<ScriptRemoveCron> commandScriptRemoveCron = std::static_pointer_cast<ScriptRemoveCron>(command);

	// TODO
	// remove cron task for a component

    //std::cout << commandScriptRemoveCron << std::endl;
}

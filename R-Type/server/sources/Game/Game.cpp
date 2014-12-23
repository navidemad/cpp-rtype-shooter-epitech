#include "Game.hpp"
#include "GameException.hpp"
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
#include <map>

const NGame::Game::tokenExec NGame::Game::tokenExecTab[] = {
	{ IScriptCommand::Instruction::NAME, &NGame::Game::scriptCommandName },
	{ IScriptCommand::Instruction::REQUIRE, &NGame::Game::scriptCommandRequire },
	{ IScriptCommand::Instruction::SPAWN, &NGame::Game::scriptCommandSpawn }
};

NGame::Game::Game(const NGame::Properties& properties, const std::shared_ptr<Script>& script) :
mScript(script),
mIndex(0),
mListener(nullptr),
mProperties(properties),
mState(NGame::Game::State::NOT_STARTED),
mMutex(PortabilityBuilder::getMutex()),
mPullEnded(true),
mCurrentComponentMaxId(Config::Game::minIdComponent)
{
}

NGame::Game::~Game(void) {

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
		Utils::logError(e.what());
		setState(NGame::Game::State::DONE);
	}

	setPullEnded(true);
}

void NGame::Game::broadcastMap(void) {
    while (getScript()->last(mIndex) == false)
    {
        const IScriptCommand* currentCommand = getScript()->get(mIndex);
		if (getCurrentFrame() < currentCommand->getFrame())
			return;
		for (const auto& instr : tokenExecTab) {
			if (instr.commandCode == currentCommand->getInstruction()) {
				(this->*instr.fctPtr)(currentCommand);
				break;
			}
		}
        ++mIndex;
    }
	setState(NGame::Game::State::DONE);
	logInfo("Level finished");
}

void NGame::Game::checkCollisions(void) {
    return;
	auto& components = getComponents();
	for (auto it = components.begin(); it != components.end();) {
		if (collision(*it))
		{
			if ((*it).getType() == IResource::Type::PLAYER) // exception quand on spam SPACE
			{
				const auto& user = findUserById((*it).getId());
				if (user != getUsers().end())
					transferPlayerToSpectators(*user);
			}
			auto listener = getListener();
		    if (listener)
		    	listener->onNotifyUsersComponentRemoved(getUsers(), (*it).getId());
			it = components.erase(it);
		}
		else
			++it;
	}
}

void NGame::Game::moveEntities(void) {
	Scopedlock(mMutex);

	for (auto& component : mComponents)
		if (component.getType() != IResource::Type::PLAYER)
			updatePositionComponent(component);
}

/*
** getters
*/
std::shared_ptr<Script>& NGame::Game::getScript(void) {
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

std::vector<NGame::User>& NGame::Game::getUsers(void) {
	Scopedlock(mMutex);

	return mUsers;
}

std::vector<NGame::Component>& NGame::Game::getComponents(void) {
	Scopedlock(mMutex);

	return mComponents;
}

NGame::Game::State& NGame::Game::getState(void) {
	Scopedlock(mMutex);

	return mState;
}

const Peer& NGame::Game::getOwner(void) {
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
void NGame::Game::setScript(std::shared_ptr<Script>& script) {
	Scopedlock(mMutex);

	mScript = script;
}

void NGame::Game::setListener(NGame::Game::OnGameEvent* listener) {
	Scopedlock(mMutex);

	mListener = listener;
}

void NGame::Game::setProperties(NGame::Properties& properties) {
	Scopedlock(mMutex);

	mProperties = properties;
}

void NGame::Game::setUsers(std::vector<NGame::User>& users) {
	Scopedlock(mMutex);

	mUsers = users;
}

void NGame::Game::setComponents(std::vector<NGame::Component>& components) {
	Scopedlock(mMutex);

	mComponents = components;
}

void NGame::Game::setState(NGame::Game::State state) {
	Scopedlock(mMutex);

	mState = state;
}

void NGame::Game::initTimer(void) {
    Scopedlock(mMutex);

    mTimer = std::clock();
}

void NGame::Game::setMutex(std::shared_ptr<IMutex>& mutex) {
	mMutex = mutex;
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

/*
** check :: collision
*/
bool NGame::Game::collision(NGame::Component& component) {
	static const auto& functionsHandleCollision = std::vector<std::function<bool(NGame::Component&, NGame::Component&)>>
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
	return (false);
}

bool NGame::Game::collisionTouch(const NGame::Component& component, const NGame::Component& obstacle) const {
	if (&obstacle == &component)
		return false;

    if (component.getX() < Config::Window::xMin || component.getX() > Config::Window::xMax || component.getY() < Config::Window::yMin || component.getX() > Config::Window::yMax)
	{
		std::cout << "####### ID: '" << component.getId() << "' OUT OF SCREEN ########" << std::endl;
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
		const auto& user = findUserById(obstacle.getId());
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
		const auto& user = findUserById(component.getId());
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
std::vector<NGame::User>::iterator NGame::Game::findIteratorUserByHost(const Peer &peer) {
	return std::find_if(mUsers.begin(), mUsers.end(), [&](const NGame::User& user) { return user.getPeer() == peer; });
}

NGame::User& NGame::Game::findUserByHost(const Peer &peer) {
	Scopedlock(mMutex);

	std::vector<NGame::User>::iterator it = std::find_if(mUsers.begin(), mUsers.end(), [&](const NGame::User& user) { return user.getPeer() == peer; });
	if (it == mUsers.end())
		throw GameException("user not found for this peer");

	return *it;
}

std::vector<NGame::User>::iterator NGame::Game::findUserById(uint64_t id) {
	return std::find_if(getUsers().begin(), getUsers().end(), [&id](const NGame::User& user) { return user.getId() == id; });
}

std::vector<NGame::Component>::iterator NGame::Game::findComponentById(uint64_t id) {
	return std::find_if(mComponents.begin(), mComponents.end(), [&id](const NGame::Component& component) { return component.getId() == id; });
}

/*
** workflow internal game
*/
void NGame::Game::addComponentInList(const NGame::Component& component) {
	Scopedlock(mMutex);

	mComponents.push_back(component);
}

void NGame::Game::addUserInList(const NGame::User& user) {
	Scopedlock(mMutex);

	mUsers.push_back(user);
}

void NGame::Game::eraseUserOfList(std::vector<NGame::User>::iterator& it) {
	Scopedlock(mMutex);

	mUsers.erase(it);
}

void NGame::Game::tryAddPlayer(NGame::User& user) {
	if (getProperties().getNbPlayers() >= getProperties().getMaxPlayers())
		throw GameException("No place for new players");

	NGame::Component component;

    double playerWidth = 0.04;
    double playerHeight = 0.04;
	double playerSpeed = 0.45;
	short playerAngle = 0;

	setCurrentComponentMaxId(getCurrentComponentMaxId() + 1);

	component.setX(1.);
    component.setY(Config::Window::yMax / 2.);
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

    const auto listener = getListener();
    if (listener)
    	listener->onNotifyUsersComponentAdded(getUsers(), component);

    if (getState() == NGame::Game::State::NOT_STARTED)
    {
        initTimer();
        setState(NGame::Game::State::RUNNING);
    }
}

void NGame::Game::tryDelPlayer(void) {
	getProperties().setNbPlayers(getProperties().getNbPlayers() - 1);
}

void NGame::Game::tryAddSpectator(const NGame::User& user) {
	if (getProperties().getNbSpectators() >= getProperties().getMaxSpectators())
		throw GameException("No place for new spectators");

	addUserInList(user);
	getProperties().setNbSpectators(getProperties().getNbSpectators() + 1);
}

void NGame::Game::tryDelSpectator(void) {
	getProperties().setNbSpectators(getProperties().getNbSpectators() - 1);
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

	const auto listener = getListener();
	if (listener)
		listener->onNotifyTimeElapsedPing(peer, getCurrentFrame());
}

void NGame::Game::delUser(const Peer &peer) {
	std::vector<NGame::User>::iterator user;
	NGame::USER_TYPE type;

	{
		Scopedlock(mMutex);

		user = findIteratorUserByHost(peer);
		if (user == mUsers.end())
			throw GameException("Try to delete an undefined address ip");

		type = user->getType();
	}

	if (type == NGame::USER_TYPE::PLAYER)
		tryDelPlayer();
	else if (type == NGame::USER_TYPE::SPECTATOR)
		tryDelSpectator();

	eraseUserOfList(user);
}

void NGame::Game::transferPlayerToSpectators(NGame::User& user) {
	const auto listener = getListener();
    if (listener)
    	listener->onRemovePeerFromWhiteList(user.getPeer());
	tryDelPlayer();
	user.setType(NGame::USER_TYPE::SPECTATOR);
	tryAddSpectator(user);
}

void NGame::Game::updatePositionComponent(NGame::Component& component) {
	double pi = 3.14159265358979323846;
	double angleInRad = component.getAngle() * pi / 180;
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
	Scopedlock(mMutex);
	NGame::Component component;
	
	double bulletWidth = 32.;
	double bulletHeight = 32.;
	double bulletSpeed = 0.0016;
	short bulletAngle = 0;
	
	const auto& user = findIteratorUserByHost(peer);
	if (user == mUsers.end())
		throw GameException("fire a player that not in this game");

	const auto& component_user = findComponentById((*user).getId());
	if (component_user == mComponents.end())
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

	mComponents.push_back(component);

	return component;
}

const NGame::Component& NGame::Game::move(const Peer &peer, IResource::Direction direction) {
	Scopedlock(mMutex);

	const auto& user = findIteratorUserByHost(peer);
	if (user == mUsers.end())
		throw GameException("fire a player that not in this game");

	const auto& component = findComponentById((*user).getId());
	if (component == mComponents.end())
		throw GameException("NGame::Game::move component_user that not in this game");

    (*component).setAngle(Config::Game::angleTab[direction]);
	updatePositionComponent(*component);

	return *component;
}

/*
** workflow scripts actions
*/
void	NGame::Game::scriptCommandName(const IScriptCommand* command) {
	auto commandScriptName = dynamic_cast<const ScriptName*>(command);

    if (!commandScriptName)
    	return;

	if (commandScriptName->getStageName() != getProperties().getLevelName())
		throw GameException("script name request doesn't match with the level name of current game");
}

void	NGame::Game::scriptCommandRequire(const IScriptCommand* command) {
	auto commandScriptRequire = dynamic_cast<const ScriptName*>(command);

    if (!commandScriptRequire)
    	return;
}

void	NGame::Game::scriptCommandSpawn(const IScriptCommand* command) {
	auto commandScriptSpawn = dynamic_cast<const ScriptName*>(command);

    if (!commandScriptSpawn)
    	return;
}

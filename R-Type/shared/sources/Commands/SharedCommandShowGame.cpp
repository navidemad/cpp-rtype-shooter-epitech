#include "CommandShowGame.hpp"

CommandShowGame::CommandShowGame(void) : mName(""), mLevelName(""), mNbPlayers(0), mMaxPlayers(0), mNbObservers(0), mMaxObservers(0) {
}

CommandShowGame::~CommandShowGame(void) {
}

const std::string &CommandShowGame::getName(void) const {
	return mName;
}

const std::string &CommandShowGame::getLevelName(void) const {
	return mLevelName;
}

char CommandShowGame::getNbPlayers(void) const {
	return mNbPlayers;
}

char CommandShowGame::getMaxPlayers(void) const {
	return mMaxPlayers;
}

char CommandShowGame::getNbObservers(void) const {
	return mNbObservers;
}

char CommandShowGame::getMaxObservers(void) const {
	return mMaxObservers;
}

void CommandShowGame::setName(const std::string &name) {
	mName = name;
}

void CommandShowGame::setLevelName(const std::string &levelName) {
	mLevelName = levelName;
}

void CommandShowGame::setNbPlayers(char nbPlayers) {
	mNbPlayers = nbPlayers;
}

void CommandShowGame::setMaxPlayers(char maxPlayers) {
	mMaxPlayers = maxPlayers;
}

void CommandShowGame::setNbObservers(char nbObservers) {
	mNbObservers = nbObservers;
}

void CommandShowGame::setMaxObservers(char maxObservers) {
	mMaxObservers = maxObservers;
}

ICommand::Instruction	CommandShowGame::getInstruction(void) const {
	return ICommand::Instruction::SHOW_GAME;
}

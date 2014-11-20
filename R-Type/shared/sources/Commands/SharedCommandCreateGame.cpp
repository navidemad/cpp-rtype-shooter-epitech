#include "CommandCreateGame.hpp"

CommandCreateGame::CommandCreateGame(void) : mName(""), mLevelName(""), mNbPlayers(0), mNbSpectators(0) {
}

CommandCreateGame::~CommandCreateGame(void) {
}

const std::string &CommandCreateGame::getName(void) const {
	return mName;
}

const std::string &CommandCreateGame::getLevelName(void) const {
	return mLevelName;
}

char CommandCreateGame::getNbPlayers(void) const {
	return mNbPlayers;
}

char CommandCreateGame::getNbSpectators(void) const {
	return mNbSpectators;
}

void CommandCreateGame::setName(const std::string &name) {
	mName = name;
}

void CommandCreateGame::setLevelName(const std::string &levelName) {
	mLevelName = levelName;
}

void CommandCreateGame::setNbPlayers(char nbPlayers) {
	mNbPlayers = nbPlayers;
}

void CommandCreateGame::setNbSpectators(char nbSpectators) {
	mNbSpectators = nbSpectators;
}

ICommand::Instruction CommandCreateGame::getInstruction(void) const {
	return ICommand::Instruction::CREATE_GAME;
}

#include "CommandObserveGame.hpp"

CommandObserveGame::CommandObserveGame(void) : mName("") {
}

CommandObserveGame::~CommandObserveGame(void) {
}

const std::string &CommandObserveGame::getName(void) const {
	return mName;
}

void CommandObserveGame::setName(const std::string &name) {
	mName = name;
}

ICommand::Instruction	CommandObserveGame::getInstruction(void) const {
	return ICommand::Instruction::OBSERVE_GAME;
}

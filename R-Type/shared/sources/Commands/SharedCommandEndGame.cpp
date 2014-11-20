#include "CommandEndGame.hpp"

CommandEndGame::CommandEndGame(void) : mName("") {
}

CommandEndGame::~CommandEndGame(void) {
}

const std::string &CommandEndGame::getName(void) const {
	return mName;
}

void CommandEndGame::setName(const std::string &name) {
	mName = name;
}

ICommand::Instruction	CommandEndGame::getInstruction(void) const {
	return ICommand::Instruction::END_GAME;
}

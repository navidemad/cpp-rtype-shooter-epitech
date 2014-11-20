#include "CommandJoinGame.hpp"

CommandJoinGame::CommandJoinGame(void) : mName("") {
}

CommandJoinGame::~CommandJoinGame(void) {
}

const std::string &CommandJoinGame::getName(void) const {
	return mName;
}

void CommandJoinGame::setName(const std::string &name) {
	mName = name;
}

ICommand::Instruction	CommandJoinGame::getInstruction(void) const {
	return ICommand::Instruction::JOIN_GAME;
}

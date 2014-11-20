#include "CommandDeleteGame.hpp"

CommandDeleteGame::CommandDeleteGame(void) : mName("") {
}

CommandDeleteGame::~CommandDeleteGame(void) {
}

const std::string &CommandDeleteGame::getName(void) const {
	return mName;
}

void CommandDeleteGame::setName(const std::string &name) {
	mName = name;
}

ICommand::Instruction	CommandDeleteGame::getInstruction(void) const {
	return ICommand::Instruction::DELETE_GAME;
}

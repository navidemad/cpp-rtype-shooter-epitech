#include "CommandLeaveGame.hpp"

CommandLeaveGame::CommandLeaveGame(void) : mName("") {
}

CommandLeaveGame::~CommandLeaveGame(void) {
}

const std::string &CommandLeaveGame::getName(void) const {
	return mName;
}

void CommandLeaveGame::setName(const std::string &name) {
	mName = name;
}

ICommand::Instruction	CommandLeaveGame::getInstruction(void) const {
	return ICommand::Instruction::LEAVE_GAME;
}

#include "CommandLeaveGame.hpp"

CommandLeaveGame::CommandLeaveGame(void) {
}

CommandLeaveGame::~CommandLeaveGame(void) {
}

ICommand::Instruction	CommandLeaveGame::getInstruction(void) const {
	return ICommand::Instruction::LEAVE_GAME;
}

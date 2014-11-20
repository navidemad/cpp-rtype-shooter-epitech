#include "CommandListGames.hpp"

CommandListGames::CommandListGames(void) {
}

CommandListGames::~CommandListGames(void) {
}

ICommand::Instruction	CommandListGames::getInstruction(void) const {
	return ICommand::Instruction::LIST_GAMES;
}

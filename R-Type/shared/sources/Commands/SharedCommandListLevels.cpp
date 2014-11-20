#include "CommandListLevels.hpp"

CommandListLevels::CommandListLevels(void) {
}

CommandListLevels::~CommandListLevels(void) {
}

ICommand::Instruction	CommandListLevels::getInstruction(void) const {
	return ICommand::Instruction::LIST_LEVELS;
}

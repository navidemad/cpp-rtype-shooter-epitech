#include "CommandFire.hpp"

CommandFire::CommandFire(void) {
}

CommandFire::~CommandFire(void) {
}

ICommand::Instruction	CommandFire::getInstruction(void) const {
	return ICommand::Instruction::FIRE;
}

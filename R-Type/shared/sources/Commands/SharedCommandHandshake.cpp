#include "CommandHandshake.hpp"

CommandHandshake::CommandHandshake(void) {
}

CommandHandshake::~CommandHandshake(void) {
}

ICommand::Instruction	CommandHandshake::getInstruction(void) const {
	return ICommand::Instruction::HANDSHAKE;
}

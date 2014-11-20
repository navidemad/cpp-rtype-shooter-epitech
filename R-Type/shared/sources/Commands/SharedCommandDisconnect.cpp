#include "CommandDisconnect.hpp"

CommandDisconnect::CommandDisconnect(void) {
}

CommandDisconnect::~CommandDisconnect(void) {
}

ICommand::Instruction	CommandDisconnect::getInstruction(void) const {
	return ICommand::Instruction::DISCONNECT;
}

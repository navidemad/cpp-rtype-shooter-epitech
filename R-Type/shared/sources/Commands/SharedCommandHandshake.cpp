#include "CommandHandshake.hpp"

CommandHandshake::CommandHandshake(void) : mUdpPort(0) {
}

CommandHandshake::~CommandHandshake(void) {
}

ICommand::Instruction	CommandHandshake::getInstruction(void) const {
	return ICommand::Instruction::HANDSHAKE;
}

int CommandHandshake::getUdpPort(void) const {
	return mUdpPort;
}

void CommandHandshake::setUdpPort(int udpPort) {
	mUdpPort = udpPort;
}

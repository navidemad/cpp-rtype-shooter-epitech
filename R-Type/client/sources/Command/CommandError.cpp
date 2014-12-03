#include "CommandError.hpp"
#include "CommandException.hpp"


IClientSocket::Message CommandError::getMessage(void) const {
	throw CommandException("This command can not be sent by the client");
}

unsigned int CommandError::getSizeToRead(void) const {
	return sizeof(CommandError::PacketFromServer);
}

void CommandError::initFromMessage(const IClientSocket::Message & message) {
	if (message.msgSize != sizeof(CommandError::PacketFromServer))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandError::PacketFromServer *>(message.msg.data());

	mInstructionCode = packet.instructionCode;
	mErrorCode = packet.errorCode;
}

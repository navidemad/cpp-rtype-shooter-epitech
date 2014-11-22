#include "CommandError.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandError::getMessage(void) const {
	CommandError::PacketFromServer packet;
	packet.instructionCode = mInstructionCode;
	packet.errorCode = mErrorCode;

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandError::PacketFromServer);

	return message;
}

unsigned int CommandError::getSizeToRead(void) const {
	throw CommandException("This command can not be received by the server");
}

void CommandError::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("This command can not be received by the server");
}

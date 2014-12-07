#include "CommandListLevels.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandListLevels::getMessage(void) const {
	IClientSocket::Message message;
	message.msgSize = 0;

	return message;
}

unsigned int CommandListLevels::getSizeToRead(void) const {
	throw CommandException("This command can not be receive by the client");
}

void CommandListLevels::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("This command can not be receive by the client");
}
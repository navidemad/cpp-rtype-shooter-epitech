#include "CommandListLevels.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandListLevels::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandListLevels::getSizeToRead(void) const {
	return 0;
}

void CommandListLevels::initFromMessage(const IClientSocket::Message &) {
}

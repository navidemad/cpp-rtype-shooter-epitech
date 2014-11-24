#include "CommandDisconnect.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandDisconnect::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandDisconnect::getSizeToRead(void) const {
	return 0;
}

void CommandDisconnect::initFromMessage(const IClientSocket::Message &) {
}

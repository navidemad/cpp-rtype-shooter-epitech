#include "CommandLeaveGame.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandLeaveGame::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandLeaveGame::getSizeToRead(void) const {
	return 0;
}

void CommandLeaveGame::initFromMessage(const IClientSocket::Message &) {
}

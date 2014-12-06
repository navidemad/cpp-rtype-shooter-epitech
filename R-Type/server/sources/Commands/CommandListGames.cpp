#include "CommandListGames.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandListGames::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandListGames::getSizeToRead(void) const {
	return 0;
}

void CommandListGames::initFromMessage(const IClientSocket::Message &) {
}

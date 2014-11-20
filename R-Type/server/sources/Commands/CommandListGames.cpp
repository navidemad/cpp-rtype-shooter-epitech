#include "CommandListGames.hpp"

IClientSocket::Message CommandListGames::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandListGames::getSizeToRead(void) const {
	return 0;
}

void CommandListGames::initFromMessage(const IClientSocket::Message &) {
}

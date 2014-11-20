#include "CommandJoinGame.hpp"

IClientSocket::Message CommandJoinGame::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandJoinGame::getSizeToRead(void) const {
	return 0;
}

void CommandJoinGame::initFromMessage(const IClientSocket::Message &) {
}

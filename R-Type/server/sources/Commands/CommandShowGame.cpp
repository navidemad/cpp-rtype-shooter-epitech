#include "CommandShowGame.hpp"

IClientSocket::Message CommandShowGame::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandShowGame::getSizeToRead(void) const {
	return 0;
}

void CommandShowGame::initFromMessage(const IClientSocket::Message &) {
}

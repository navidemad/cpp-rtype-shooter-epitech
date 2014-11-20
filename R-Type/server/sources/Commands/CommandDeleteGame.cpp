#include "CommandDeleteGame.hpp"

IClientSocket::Message CommandDeleteGame::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandDeleteGame::getSizeToRead(void) const {
	return 0;
}

void CommandDeleteGame::initFromMessage(const IClientSocket::Message &) {
}

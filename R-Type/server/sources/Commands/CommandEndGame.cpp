#include "CommandEndGame.hpp"

IClientSocket::Message CommandEndGame::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandEndGame::getSizeToRead(void) const {
	return 0;
}

void CommandEndGame::initFromMessage(const IClientSocket::Message &) {
}

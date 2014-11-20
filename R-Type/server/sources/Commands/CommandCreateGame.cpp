#include "CommandCreateGame.hpp"

IClientSocket::Message CommandCreateGame::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandCreateGame::getSizeToRead(void) const {
	return 0;
}

void CommandCreateGame::initFromMessage(const IClientSocket::Message &) {
}

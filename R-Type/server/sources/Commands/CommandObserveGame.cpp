#include "CommandObserveGame.hpp"

IClientSocket::Message CommandObserveGame::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandObserveGame::getSizeToRead(void) const {
	return 0;
}

void CommandObserveGame::initFromMessage(const IClientSocket::Message &) {
}

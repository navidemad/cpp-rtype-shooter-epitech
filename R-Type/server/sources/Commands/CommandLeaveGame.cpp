#include "CommandLeaveGame.hpp"

IClientSocket::Message CommandLeaveGame::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandLeaveGame::getSizeToRead(void) const {
	return 0;
}

void CommandLeaveGame::initFromMessage(const IClientSocket::Message &) {
}

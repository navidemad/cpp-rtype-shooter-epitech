#include "CommandTimeElapsedPing.hpp"

IClientSocket::Message CommandTimeElapsedPing::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandTimeElapsedPing::getSizeToRead(void) const {
	return 0;
}

void CommandTimeElapsedPing::initFromMessage(const IClientSocket::Message &) {
}

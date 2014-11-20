#include "CommandShowLevel.hpp"

IClientSocket::Message CommandShowLevel::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandShowLevel::getSizeToRead(void) const {
	return 0;
}

void CommandShowLevel::initFromMessage(const IClientSocket::Message &) {
}

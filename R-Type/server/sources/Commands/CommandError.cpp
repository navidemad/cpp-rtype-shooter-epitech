#include "CommandError.hpp"

IClientSocket::Message CommandError::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandError::getSizeToRead(void) const {
	return 0;
}

void CommandError::initFromMessage(const IClientSocket::Message &) {
}

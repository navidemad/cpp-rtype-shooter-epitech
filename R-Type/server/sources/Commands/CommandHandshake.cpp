#include "CommandHandshake.hpp"

IClientSocket::Message CommandHandshake::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandHandshake::getSizeToRead(void) const {
	return 0;
}

void CommandHandshake::initFromMessage(const IClientSocket::Message &) {
}

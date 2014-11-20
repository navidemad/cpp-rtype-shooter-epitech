#include "CommandFire.hpp"

IClientSocket::Message CommandFire::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandFire::getSizeToRead(void) const {
	return 0;
}

void CommandFire::initFromMessage(const IClientSocket::Message &) {
}

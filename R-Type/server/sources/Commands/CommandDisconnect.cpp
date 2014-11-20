#include "CommandDisconnect.hpp"

IClientSocket::Message CommandDisconnect::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandDisconnect::getSizeToRead(void) const {
	return 0;
}

void CommandDisconnect::initFromMessage(const IClientSocket::Message &) {
}

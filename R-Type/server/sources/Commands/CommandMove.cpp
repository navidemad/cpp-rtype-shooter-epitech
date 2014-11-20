#include "CommandMove.hpp"

IClientSocket::Message CommandMove::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandMove::getSizeToRead(void) const {
	return 0;
}

void CommandMove::initFromMessage(const IClientSocket::Message &) {
}

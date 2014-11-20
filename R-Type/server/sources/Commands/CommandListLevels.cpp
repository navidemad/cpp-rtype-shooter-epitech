#include "CommandListLevels.hpp"

IClientSocket::Message CommandListLevels::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandListLevels::getSizeToRead(void) const {
	return 0;
}

void CommandListLevels::initFromMessage(const IClientSocket::Message &) {
}

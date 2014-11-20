#include "CommandUpdateScore.hpp"

IClientSocket::Message CommandUpdateScore::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandUpdateScore::getSizeToRead(void) const {
	return 0;
}

void CommandUpdateScore::initFromMessage(const IClientSocket::Message &) {
}

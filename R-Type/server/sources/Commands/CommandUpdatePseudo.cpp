#include "CommandUpdatePseudo.hpp"

IClientSocket::Message CommandUpdatePseudo::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandUpdatePseudo::getSizeToRead(void) const {
	return 0;
}

void CommandUpdatePseudo::initFromMessage(const IClientSocket::Message &) {
}

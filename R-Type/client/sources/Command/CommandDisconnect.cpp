#include "CommandDisconnect.hpp"

IClientSocket::Message CommandDisconnect::getMessage(void) const {
	IClientSocket::Message message;
	message.msgSize = 0;

	return message;
}

unsigned int CommandDisconnect::getSizeToRead(void) const {
	throw std::string("This command can not be receive by the client");
}

void CommandDisconnect::initFromMessage(const IClientSocket::Message &) {
	throw std::string("This command can not be receive by the client");
}
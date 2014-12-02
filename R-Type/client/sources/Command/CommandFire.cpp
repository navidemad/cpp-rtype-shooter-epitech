#include "CommandFire.hpp"

IClientSocket::Message CommandFire::getMessage(void) const {
	IClientSocket::Message message;
	message.msg.clear();
	message.msgSize = 0;

	return message;
}

unsigned int CommandFire::getSizeToRead(void) const {
	throw std::string("This command can not be receive by the client");
}

void CommandFire::initFromMessage(const IClientSocket::Message &) {
	throw std::string("This command can not be receive by the client");
}

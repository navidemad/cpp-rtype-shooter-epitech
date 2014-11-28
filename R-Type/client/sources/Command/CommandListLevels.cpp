#include "CommandListLevels.hpp"

IClientSocket::Message CommandListLevels::getMessage(void) const {
	IClientSocket::Message message;
	message.msgSize = 0;
	message.msg.clear();

	return message;
}

unsigned int CommandListLevels::getSizeToRead(void) const {
	throw std::string("This command can not be receive by the client");
}

void CommandListLevels::initFromMessage(const IClientSocket::Message &) {
	throw std::string("This command can not be receive by the client");
}
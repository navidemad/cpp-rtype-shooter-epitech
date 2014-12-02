#include "CommandListGames.hpp"

IClientSocket::Message CommandListGames::getMessage(void) const {
	IClientSocket::Message message;
	message.msg.clear();
	message.msgSize = 0;

	return message;
}

unsigned int CommandListGames::getSizeToRead(void) const {
	throw std::string("This command can not be receive by the client");
}

void CommandListGames::initFromMessage(const IClientSocket::Message &) {
	throw std::string("This command can not be receive by the client");
}
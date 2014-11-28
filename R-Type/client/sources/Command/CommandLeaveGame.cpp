#include "CommandLeaveGame.hpp"

IClientSocket::Message CommandLeaveGame::getMessage(void) const {
	IClientSocket::Message message;
	message.msg.clear();
	message.msgSize = 0;

	return message;
}

unsigned int CommandLeaveGame::getSizeToRead(void) const {
	throw std::string("This command can not be receive by the client");
}

void CommandLeaveGame::initFromMessage(const IClientSocket::Message &message) {
	throw std::string("This command can not be receive by the client");
}
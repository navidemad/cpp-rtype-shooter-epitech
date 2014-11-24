#include "CommandListLevels.hpp"

IClientSocket::Message CommandListLevels::getMessage(void) const {
	IClientSocket::Message message;
	message.msgSize = 0;

	return message;
}

unsigned int CommandListLevels::getSizeToRead(void) const {
	return sizeof(CommandListLevels::PacketFromClient);
}

void CommandListLevels::initFromMessage(const IClientSocket::Message &) {
}

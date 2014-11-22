#include "CommandListGames.hpp"

IClientSocket::Message CommandListGames::getMessage(void) const {
	IClientSocket::Message message;
	message.msgSize = 0;

	return message;
}

unsigned int CommandListGames::getSizeToRead(void) const {
	return sizeof(CommandListGames::PacketFromClient);
}

void CommandListGames::initFromMessage(const IClientSocket::Message &) {
}

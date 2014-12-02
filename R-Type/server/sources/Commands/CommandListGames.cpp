#include "CommandListGames.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandListGames::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandListGames::getSizeToRead(void) const {
	return sizeof(CommandListGames::PacketFromClient);
}

void CommandListGames::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandListGames::PacketFromClient))
		throw CommandException("Packet has an invalid size");
}

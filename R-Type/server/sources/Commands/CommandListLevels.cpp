#include "CommandListLevels.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandListLevels::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandListLevels::getSizeToRead(void) const {
	return sizeof(CommandListLevels::PacketFromClient);
}

void CommandListLevels::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandListLevels::PacketFromClient))
		throw CommandException("Packet has an invalid size");
}

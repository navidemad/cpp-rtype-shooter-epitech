#include "CommandFire.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandFire::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandFire::getSizeToRead(void) const {
	return sizeof(CommandFire::PacketFromClient);
}

void CommandFire::initFromMessage(const IClientSocket::Message &) {
}

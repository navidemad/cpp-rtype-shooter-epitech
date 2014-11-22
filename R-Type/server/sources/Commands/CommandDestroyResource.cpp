#include "CommandDestroyResource.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandDestroyResource::getMessage(void) const {
	CommandDestroyResource::PacketFromServer packet;
	packet.id = mId;

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandDestroyResource::PacketFromServer);

	return message;
}

unsigned int CommandDestroyResource::getSizeToRead(void) const {
	throw CommandException("This command can not be received by the server");
}

void CommandDestroyResource::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("This command can not be received by the server");
}

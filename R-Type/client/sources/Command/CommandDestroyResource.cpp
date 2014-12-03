#include "CommandDestroyResource.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandDestroyResource::getMessage(void) const {
	throw CommandException("This command can not be send by the client");
}

unsigned int CommandDestroyResource::getSizeToRead(void) const {
	return sizeof(CommandDestroyResource::PacketFromServer);
}

void CommandDestroyResource::initFromMessage(const IClientSocket::Message & message) {
	if (message.msgSize != sizeof(CommandDestroyResource::PacketFromServer))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandDestroyResource::PacketFromServer *>(message.msg.data());

	mId = packet.id;
}
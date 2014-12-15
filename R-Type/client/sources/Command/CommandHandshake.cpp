#include "CommandHandshake.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandHandshake::getMessage(void) const {
	CommandHandshake::PacketFromClient packet;
	packet.udpPort = mUdpPort;

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandHandshake::PacketFromClient);

	return message;
}

unsigned int CommandHandshake::getSizeToRead(void) const {
	return sizeof(CommandHandshake::PacketFromServer);
}

void CommandHandshake::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandHandshake::PacketFromServer))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandHandshake::PacketFromServer *>(message.msg.data());

	mUdpPort = packet.udpPort;
}

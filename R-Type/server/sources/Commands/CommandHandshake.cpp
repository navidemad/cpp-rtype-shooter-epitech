#include "CommandHandshake.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandHandshake::getMessage(void) const {
	CommandHandshake::PacketFromServer packet;
	packet.udpPort = mUdpPort;

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandHandshake::PacketFromServer);

	return message;
}

unsigned int CommandHandshake::getSizeToRead(void) const {
	return sizeof(CommandHandshake::PacketFromClient);
}

void CommandHandshake::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandHandshake::PacketFromClient))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandHandshake::PacketFromClient *>(message.msg.data());

	mUdpPort = packet.udpPort;
}

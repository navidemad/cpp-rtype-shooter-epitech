#include "CommandJoinGame.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandJoinGame::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandJoinGame::getSizeToRead(void) const {
	return sizeof(CommandJoinGame::PacketFromClient);
}

void CommandJoinGame::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandJoinGame::PacketFromClient))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandJoinGame::PacketFromClient *>(message.msg.data());

	packet.name[sizeof(packet.name) - 1] = 0;
	mName = packet.name;
}

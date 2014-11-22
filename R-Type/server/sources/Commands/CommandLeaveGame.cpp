#include "CommandLeaveGame.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandLeaveGame::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandLeaveGame::getSizeToRead(void) const {
	return sizeof(CommandLeaveGame::PacketFromClient);
}

void CommandLeaveGame::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandLeaveGame::PacketFromClient))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandLeaveGame::PacketFromClient *>(message.msg.data());

	packet.name[sizeof(packet.name) - 1] = 0;
	mName = packet.name;
}

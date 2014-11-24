#include "CommandDeleteGame.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandDeleteGame::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandDeleteGame::getSizeToRead(void) const {
	return sizeof(CommandDeleteGame::PacketFromClient);
}

void CommandDeleteGame::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandDeleteGame::PacketFromClient))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandDeleteGame::PacketFromClient *>(message.msg.data());

	packet.name[sizeof(packet.name) - 1] = 0;
	mName = packet.name;
}

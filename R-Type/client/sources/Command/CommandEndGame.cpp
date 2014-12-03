#include "CommandEndGame.hpp"
#include "CommandException.hpp"
#include <algorithm>
#include <cstring>

IClientSocket::Message CommandEndGame::getMessage(void) const {
	throw CommandException("This command can not be sent by the client");
}

unsigned int CommandEndGame::getSizeToRead(void) const {
	return sizeof(CommandEndGame::PacketFromServer);
}

void CommandEndGame::initFromMessage(const IClientSocket::Message & message) {
	if (message.msgSize != sizeof(CommandEndGame::PacketFromServer))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandEndGame::PacketFromServer *>(message.msg.data());

	packet.name[sizeof(packet.name) - 1] = 0;

	mName = packet.name;
}
#include "CommandShowLevel.hpp"
#include "CommandException.hpp"
#include <algorithm>
#include <cstring>

IClientSocket::Message CommandShowLevel::getMessage(void) const {
	throw CommandException("This command can not be sent by the client");
}

unsigned int CommandShowLevel::getSizeToRead(void) const {
	return sizeof(CommandShowLevel::PacketFromServer);
}

void CommandShowLevel::initFromMessage(const IClientSocket::Message & message) {
	if (message.msgSize != sizeof(CommandShowLevel::PacketFromServer))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandShowLevel::PacketFromServer *>(message.msg.data());

	packet.name[sizeof(packet.name) - 1] = 0;
	packet.script[sizeof(packet.script) - 1] = 0;

	mName = packet.name;
	mScript = packet.script;
}
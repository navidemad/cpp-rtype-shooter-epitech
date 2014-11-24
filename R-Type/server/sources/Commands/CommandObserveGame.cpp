#include "CommandObserveGame.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandObserveGame::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandObserveGame::getSizeToRead(void) const {
	return sizeof(CommandObserveGame::PacketFromClient);
}

void CommandObserveGame::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandObserveGame::PacketFromClient))
		throw CommandException("Command has an invalid size");

	auto packet = *reinterpret_cast<const CommandObserveGame::PacketFromClient *>(message.msg.data());

	packet.name[sizeof(packet.name) - 1] = 0;
	mName = packet.name;
}

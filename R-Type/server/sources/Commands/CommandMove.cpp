#include "CommandMove.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandMove::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandMove::getSizeToRead(void) const {
	return sizeof(CommandMove::PacketFromClient);
}

void CommandMove::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandMove::PacketFromClient))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandMove::PacketFromClient *>(message.msg.data());
	mDirection = static_cast<IRessource::Direction>(packet.direction);
}

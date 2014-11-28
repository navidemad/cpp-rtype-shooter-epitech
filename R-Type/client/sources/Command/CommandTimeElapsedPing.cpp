#include "CommandTimeElapsedPing.hpp"

IClientSocket::Message CommandTimeElapsedPing::getMessage(void) const {
	throw CommandException("This command can not be sent by the client");
}

unsigned int CommandTimeElapsedPing::getSizeToRead(void) const {
	return sizeof(CommandTimeElapsedPing::PacketFromServer);
}

void CommandTimeElapsedPing::initFromMessage(const IClientSocket::Message &) {
	if (message.msgSize != sizeof(CommandTimeElapsedPing::PacketFromServer))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandTimeElapsedPing::PacketFromServer *>(message.msg.data());

	mTimeElapsed = packet.timeElapsed;
}

#include "CommandTimeElapsedPing.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandTimeElapsedPing::getMessage(void) const {
	CommandTimeElapsedPing::PacketFromServer packet;
	packet.timeElapsed = mTimeElapsed;

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandTimeElapsedPing::PacketFromServer);

	return message;
}

unsigned int CommandTimeElapsedPing::getSizeToRead(void) const {
	throw CommandException("This command can not be received by the server");
}

void CommandTimeElapsedPing::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("This command can not be received by the server");
}

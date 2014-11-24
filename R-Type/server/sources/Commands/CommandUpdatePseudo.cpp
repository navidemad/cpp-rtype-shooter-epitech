#include "CommandUpdatePseudo.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandUpdatePseudo::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandUpdatePseudo::getSizeToRead(void) const {
	return sizeof(CommandUpdatePseudo::PacketFromClient);
}

void CommandUpdatePseudo::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandUpdatePseudo::PacketFromClient))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandUpdatePseudo::PacketFromClient *>(message.msg.data());

	packet.pseudo[sizeof(packet.pseudo) - 1] = 0;
	mPseudo = packet.pseudo;
}

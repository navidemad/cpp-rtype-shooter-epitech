#include "CommandMoveResource.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandMoveResource::getMessage(void) const {
	CommandMoveResource::PacketFromServer packet;
	packet.type = static_cast<int>(mType);
	packet.x = mX;
	packet.y = mY;
	packet.angle = mAngle;

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandMoveResource::PacketFromServer);

	return message;
}

unsigned int CommandMoveResource::getSizeToRead(void) const {
	throw CommandException("This command can not be received by the server");
}

void CommandMoveResource::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("This command can not be received by the server");
}

#include "Network/CommandPacketBuilder.hpp"

#include <iostream>

/*
** Ctor - dtor
*/
CommandPacketBuilder::CommandPacketBuilder(CommandPacketBuilder::OnCommandEvent *listener)
 : mListener(listener) {

}

CommandPacketBuilder::~CommandPacketBuilder(){

}

/*
** Callback from ISocketClient
*/
void    CommandPacketBuilder::onBytesWritten(IClientSocket * /*socket*/, unsigned int /*nbBytes*/){
	return;
}

void    CommandPacketBuilder::onSocketReadable(IClientSocket * socket, unsigned int nbBytesToRead){
	IClientSocket::Message message;

	message = socket->receive(nbBytesToRead);
	std::string msg_str(message.msg.begin(), message.msg.end());
	std::cout << msg_str;
	socket->send(message);
}

void    CommandPacketBuilder::onSocketClosed(IClientSocket * /*socket*/){
	return ;
}

/*
** HandleCommand
*/
void CommandPacketBuilder::packCommand(IClientSocket * /*socket*/, ICommand * /*command*/){

}

void CommandPacketBuilder::unPackCommand(IClientSocket * /*socket*/){
	
}


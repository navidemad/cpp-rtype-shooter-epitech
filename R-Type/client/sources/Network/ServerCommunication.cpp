#include "Network/ServerCommunication.hpp"
#include "Network/TcpClient.hpp"

#include <iostream>

/*
** ctor - dtor
*/
ServerCommunication::ServerCommunication() {
	mSocketTcp = new TcpClient;
	mSocketTcp->setOnSocketEventListener(this);
}

ServerCommunication::~ServerCommunication() {
	delete mSocketTcp;
}

/*
** Callback from ISocketClient
*/
void    ServerCommunication::onBytesWritten(IClientSocket * /*socket*/, unsigned int /*nbBytes*/){
	return;
}
void    ServerCommunication::onSocketReadable(IClientSocket * socket, unsigned int nbBytesToRead){
	IClientSocket::Message message;

	message = socket->receive(nbBytesToRead);
	std::string msg_str(message.msg.begin(), message.msg.end());
	std::cout << msg_str;
	socket->send(message);
	return ;
}
void    ServerCommunication::onSocketClosed(IClientSocket * /*socket*/){
	return ;
}

/*
** Handle socket
*/
void ServerCommunication::connectSocketTcp(void){
	mSocketTcp->connect(mIpTcp, mPortTcp);
}

/*
** Getter
*/
std::list<ICommand *> &ServerCommunication::getCommand(void) {
	return mListCommand;
}

/*
** Setter
*/
void ServerCommunication::setServerTcp(int port, std::string ip){
	mPortTcp = port;
	mIpTcp = ip;
}
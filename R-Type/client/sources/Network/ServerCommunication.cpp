#include "Network/ServerCommunication.hpp"
#include "Network/TcpClient.hpp"

/*
** ctor - dtor
*/
ServerCommunication::ServerCommunication() 
: mHandleTcpCmd(this){
	mSocketTcp = new TcpClient;
	mSocketTcp->setOnSocketEventListener(&mHandleTcpCmd);
}

ServerCommunication::~ServerCommunication() {
	delete mSocketTcp;
}

/*
** Callback from CommandPacketBuilder
*/
void ServerCommunication::onNewCommand(ICommand *command) {
	mListCommand.push_back(command);
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
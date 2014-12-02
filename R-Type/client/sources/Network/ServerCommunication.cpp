#include "Network/ServerCommunication.hpp"
#include "Network/TcpClient.hpp"

/*
** ctor - dtor
*/
ServerCommunication::ServerCommunication() {
}

ServerCommunication::~ServerCommunication() {
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
#include "Network/ServerCommunication.hpp"
#include "Network/TcpClient.hpp"
#include <memory>

/*
** ctor - dtor
*/
ServerCommunication::ServerCommunication()
: mSocketTcp(new TcpClient()), mCmdTcp(mSocketTcp), mCmdUdp(4242){
	mCmdTcp.setListener(this);
	mCmdUdp.setListener(this);
}

ServerCommunication::~ServerCommunication() {
}

/*
** Callback from ClientPacketBuilder
*/
void    ServerCommunication::onPacketAvailable(const ClientPacketBuilder &/*clientPacketBuilder*/, const std::shared_ptr<ICommand> &/*command*/){

}
void    ServerCommunication::onSocketClosed(const ClientPacketBuilder &/*clientPacketBuilder*/){

}

/*
** Callback from PlayerPacketBuilder
*/
void ServerCommunication::onPacketAvailable(const PlayerPacketBuilder &/*clientPacketBuilder*/, const std::shared_ptr<ICommand> &/*command*/, const Peer &/*peer*/){

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
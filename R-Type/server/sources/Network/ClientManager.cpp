#include "ClientManager.hpp"
#include "PortabilityBuilder.hpp"

ClientManager::ClientManager(void) : mServer(PortabilityBuilder::getTcpServer()) {
}

ClientManager::~ClientManager(void) {
}
	
void ClientManager::onNewConnection(IServerSocket *socket) {
	mClients.push_back(Client(socket->getNewClient()));
}

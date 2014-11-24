#include "ClientManager.hpp"
#include "PortabilityBuilder.hpp"
#include "Utils.hpp"

ClientManager::ClientManager(void) : mServer(PortabilityBuilder::getTcpServer()) {
}

ClientManager::~ClientManager(void) {
	mServer->closeServer();
}
	
void ClientManager::onNewConnection(IServerSocket *socket) {
	Utils::logInfo("new client connected");

	std::shared_ptr<Client> client(new Client(socket->getNewClient()));
	client->setListener(this);
	mClients.push_back(client);
}

void ClientManager::run(void) {
	mServer->createServer(ClientManager::SERVER_TCP_PORT, ClientManager::SERVER_TCP_QUEUE);
	mServer->setOnSocketEventListener(this);
}

#include <iostream>
void	ClientManager::onClientDisconnected(const Client &client) {
	Utils::logInfo("client disconnected");
	mClients.remove_if([&](const std::shared_ptr<Client> &it) { return it.get() == &client; });
	std::cout << mClients.size() << std::endl;
}

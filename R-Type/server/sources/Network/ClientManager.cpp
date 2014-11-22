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
	client->registerObserver(Client::Event::DISCONNECTION, std::bind(&ClientManager::onClientDisconnected, this, client));
	mClients.push_back(client);
}

void ClientManager::run(void) {
	mServer->createServer(ClientManager::SERVER_TCP_PORT, ClientManager::SERVER_TCP_QUEUE);
	mServer->setOnSocketEventListener(this);
}

void	ClientManager::onClientDisconnected(const std::shared_ptr<Client> &client) {
	Utils::logInfo("client disconnected");
	mClients.remove_if([&](const std::shared_ptr<Client> &it) { return it.get() == client.get(); });
}

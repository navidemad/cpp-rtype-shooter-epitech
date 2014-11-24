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

void	ClientManager::onClientDisconnected(const Client &client) {
	Utils::logInfo("client disconnected");
	mClients.remove_if([&](const std::shared_ptr<Client> &it) { return it.get() == &client; });
}

void	ClientManager::onClientCreateGame(const Client &client, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers) {
}

void	ClientManager::onClientJoinGame(const Client &client, const std::string &name) {
}

void	ClientManager::onClientShowGame(const Client &client, const std::string &name) {
}

void	ClientManager::onClientDeleteGame(const Client &client, const std::string &name) {
}

void	ClientManager::onClientListGames(const Client &client) {
}

void	ClientManager::onClientListLevels(const Client &client) {
}

void	ClientManager::onClientDisconnect(const Client &client) {
}

void	ClientManager::onClientHandshake(const Client &client) {
}

void	ClientManager::onClientObserverGame(const Client &client, const std::string &name) {
}

void	ClientManager::onClientLeaveGame(const Client &client, const std::string &name) {
}

void	ClientManager::onClientUpdatePseudo(const Client &client, const std::string &pseudo) {
}

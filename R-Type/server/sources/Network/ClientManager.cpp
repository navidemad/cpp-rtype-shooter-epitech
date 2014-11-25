#include "ClientManager.hpp"
#include "PortabilityBuilder.hpp"
#include "Utils.hpp"

ClientManager::ClientManager(void) : mListener(nullptr), mServer(PortabilityBuilder::getTcpServer()) {
}

ClientManager::~ClientManager(void) {
	mServer->closeServer();
}

void ClientManager::onNewConnection(IServerSocket *socket) {
	Utils::logInfo("connecting new client");

	std::shared_ptr<Client> client(new Client(socket->getNewClient()));
	client->setListener(this);
	client->handshake();
	mClients.push_back(client);

	Utils::logInfo("new client connected");
}

void ClientManager::run(void) {
	mServer->createServer(ClientManager::SERVER_TCP_PORT, ClientManager::SERVER_TCP_QUEUE);
	mServer->setOnSocketEventListener(this);
}

void	ClientManager::onClientDisconnected(const Client &client) {
	Utils::logInfo("client disconnected");

	if (client.isAuthenticated() && mListener)
		mListener->onClientDisconnected(client.getHost());

	mClients.remove_if([&](const std::shared_ptr<Client> &it) { return it.get() == &client; });
}

void	ClientManager::onClientCreateGame(const Client &client, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientCreateGame(client.getHost(), name, levelName, nbPlayers, nbObservers);
}

void	ClientManager::onClientJoinGame(const Client &client, const std::string &name) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientJoinGame(client.getHost(), name, client.getPseudo());
}

void	ClientManager::onClientShowGame(const Client &client, const std::string &name) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientShowGame(client.getHost(), name);
}

void	ClientManager::onClientDeleteGame(const Client &client, const std::string &name) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientDeleteGame(client.getHost(), name);
}

void	ClientManager::onClientListGames(const Client &client) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientListGames(client.getHost());
}

void	ClientManager::onClientListLevels(const Client &client) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientListLevels(client.getHost());
}

void	ClientManager::onClientDisconnect(const Client &client) {
	onClientDisconnect(client);
}

void	ClientManager::onClientHandshake(Client &client) {
	client.setIsAuthenticated(true);
}

void	ClientManager::onClientObserveGame(const Client &client, const std::string &name) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientObserveGame(client.getHost(), name);
}

void	ClientManager::onClientLeaveGame(const Client &client) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientLeaveGame(client.getHost());
}

void	ClientManager::onClientUpdatePseudo(Client &client, const std::string &pseudo) {
	client.setPseudo(pseudo);
}

void	ClientManager::setListener(ClientManager::OnClientManagerEvent *listener) {
	mListener = listener;
}
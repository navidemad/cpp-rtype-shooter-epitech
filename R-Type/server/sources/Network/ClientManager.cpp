#include "ClientManager.hpp"
#include "PortabilityBuilder.hpp"
#include "Utils.hpp"
#include <algorithm>

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

	const auto &clientIt = findClient(client.getHost());
	if (clientIt != mClients.end())
		mClients.erase(clientIt);
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

void	ClientManager::sendError(const std::list<std::string> &hosts, const ErrorStatus &errorStatus) {
	for (const auto &host : hosts) {
		const auto &client = findClient(host);

		if (client != mClients.end())
			(*client)->sendError(errorStatus);
	}
}

void	ClientManager::sendShowGame(const std::list<std::string> &hosts, const std::string &name, const std::string &levelName, int nbPlayers, int maxPlayers, int nbObservers, int maxObservers) {
	for (const auto &host : hosts) {
		const auto &client = findClient(host);
			
		if (client != mClients.end())
			(*client)->sendShowGame(name, levelName, nbPlayers, maxPlayers, nbObservers, maxObservers);
	}
}

void	ClientManager::sendEndGame(const std::list<std::string> &hosts) {
	for (const auto &host : hosts) {
		const auto &client = findClient(host);

		if (client != mClients.end())
			(*client)->sendEndGame();
	}
}

void	ClientManager::sendShowLevel(const std::list<std::string> &hosts, const std::string &name, const std::string &script) {
	for (const auto &host : hosts) {
		const auto &client = findClient(host);

		if (client != mClients.end())
			(*client)->sendShowLevel(name, script);
	}
}

std::list<std::shared_ptr<Client>>::iterator ClientManager::findClient(const std::string &host) {
	return std::find_if(mClients.begin(), mClients.end(), [&](const std::shared_ptr<Client> &client) { return client->getHost() == host; });
}

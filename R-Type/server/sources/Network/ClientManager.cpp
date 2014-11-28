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
		mListener->onClientDisconnected(client.getPeer());

	const auto &clientIt = findClient(client.getPeer());
	if (clientIt != mClients.end())
		mClients.erase(clientIt);
}

void	ClientManager::onClientCreateGame(const Client &client, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientCreateGame(client.getPeer(), name, levelName, nbPlayers, nbObservers);
}

void	ClientManager::onClientJoinGame(const Client &client, const std::string &name) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientJoinGame(client.getPeer(), name, client.getPseudo());
}

void	ClientManager::onClientShowGame(const Client &client, const std::string &name) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientShowGame(client.getPeer(), name);
}

void	ClientManager::onClientDeleteGame(const Client &client, const std::string &name) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientDeleteGame(client.getPeer(), name);
}

void	ClientManager::onClientListGames(const Client &client) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientListGames(client.getPeer());
}

void	ClientManager::onClientListLevels(const Client &client) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientListLevels(client.getPeer());
}

void	ClientManager::onClientDisconnect(const Client &client) {
	onClientDisconnect(client);
}

void	ClientManager::onClientHandshake(Client &client) {
	client.setIsAuthenticated(true);
}

void	ClientManager::onClientObserveGame(const Client &client, const std::string &name) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientObserveGame(client.getPeer(), name);
}

void	ClientManager::onClientLeaveGame(const Client &client) {
	if (client.isAuthenticated() && mListener)
		mListener->onClientLeaveGame(client.getPeer());
}

void	ClientManager::onClientUpdatePseudo(Client &client, const std::string &pseudo) {
	if (client.isAuthenticated()) {
		client.setPseudo(pseudo);

		if (mListener)
			mListener->onClientUpdatePseudo(client.getPeer(), pseudo);
	}
}

void	ClientManager::setListener(ClientManager::OnClientManagerEvent *listener) {
	mListener = listener;
}

void	ClientManager::sendError(const std::list<Peer> &peers, const ErrorStatus &errorStatus) {
	for (const auto &peer : peers) {
		const auto &client = findClient(peer);

		if (client != mClients.end())
			(*client)->sendError(errorStatus);
	}
}

void	ClientManager::sendShowGame(const std::list<Peer> &peers, const std::string &name, const std::string &levelName, int nbPlayers, int maxPlayers, int nbObservers, int maxObservers) {
	for (const auto &peer : peers) {
		const auto &client = findClient(peer);
			
		if (client != mClients.end())
			(*client)->sendShowGame(name, levelName, nbPlayers, maxPlayers, nbObservers, maxObservers);
	}
}

void	ClientManager::sendEndGame(const std::list<Peer> &peers) {
	for (const auto &peer : peers) {
		const auto &client = findClient(peer);

		if (client != mClients.end())
			(*client)->sendEndGame();
	}
}

void	ClientManager::sendShowLevel(const std::list<Peer> &peers, const std::string &name, const std::string &script) {
	for (const auto &peer : peers) {
		const auto &client = findClient(peer);

		if (client != mClients.end())
			(*client)->sendShowLevel(name, script);
	}
}

std::list<std::shared_ptr<Client>>::iterator ClientManager::findClient(const Peer &peer) {
	return std::find_if(mClients.begin(), mClients.end(), [&](const std::shared_ptr<Client> &client) { return client->getPeer() == peer; });
}

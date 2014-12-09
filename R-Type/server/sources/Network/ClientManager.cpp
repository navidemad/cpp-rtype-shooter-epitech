#include "ClientManager.hpp"
#include "PortabilityBuilder.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include "PlayerCommunicationManager.hpp"

ClientManager::ClientManager(void) : mListener(nullptr), mServer(PortabilityBuilder::getTcpServer()) {
}

ClientManager::~ClientManager(void) {
	mServer->closeServer();
}

void ClientManager::logInfo(const Peer &peer, const std::string &log) {
	std::stringstream ss;

	ss << Utils::RED << "[TCP]" << Utils::YELLOW << "[" << peer.host << ":" << peer.tcpPort << "]> " << Utils::WHITE << log; 
	Utils::logInfo(ss.str());
}

void ClientManager::onNewConnection(IServerSocket *socket) {
	std::shared_ptr<Client> client(new Client(socket->getNewClient()));
	client->setListener(this);
	client->handshake(PlayerCommunicationManager::UDP_PORT);
	mClients.push_back(client);

	onClientHandshake(*client.get(), PlayerCommunicationManager::UDP_PORT); // debug
	onClientCreateGame(*client.get(), "game name", "level name", 4, 4); // debug
	logInfo(client->getPeer(), "Connected");
}

void ClientManager::run(void) {
	mServer->createServer(ClientManager::SERVER_TCP_PORT, ClientManager::SERVER_TCP_QUEUE);
	mServer->setOnSocketEventListener(this);
}

void	ClientManager::onClientDisconnected(const Client &client) {
	logInfo(client.getPeer(), "Disconnected");

	if (client.isAuthenticated() && mListener)
		mListener->onClientDisconnected(client.getPeer());

	const auto &clientIt = findClient(client.getPeer());
	if (clientIt != mClients.end())
		mClients.erase(clientIt);
}

void	ClientManager::onClientCreateGame(const Client &client, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers) {
	logInfo(client.getPeer(), "RECV CreateGame");

	if (client.isAuthenticated() && mListener)
		mListener->onClientCreateGame(client.getPeer(), name, levelName, nbPlayers, nbObservers);
}

void	ClientManager::onClientJoinGame(const Client &client, const std::string &name) {
	logInfo(client.getPeer(), "RECV JoinGame");

	if (client.isAuthenticated() && mListener)
		mListener->onClientJoinGame(client.getPeer(), name, client.getPseudo());
}

void	ClientManager::onClientShowGame(const Client &client, const std::string &name) {
	logInfo(client.getPeer(), "RECV ShowGame");

	if (client.isAuthenticated() && mListener)
		mListener->onClientShowGame(client.getPeer(), name);
}

void	ClientManager::onClientDeleteGame(const Client &client, const std::string &name) {
	logInfo(client.getPeer(), "RECV DeleteGame");

	if (client.isAuthenticated() && mListener)
		mListener->onClientDeleteGame(client.getPeer(), name);
}

void	ClientManager::onClientListGames(const Client &client) {
	logInfo(client.getPeer(), "RECV ListGames");

	if (client.isAuthenticated() && mListener)
		mListener->onClientListGames(client.getPeer());
}

void	ClientManager::onClientListLevels(const Client &client) {
	logInfo(client.getPeer(), "RECV ListLevels");

	if (client.isAuthenticated() && mListener)
		mListener->onClientListLevels(client.getPeer());
}

void	ClientManager::onClientHandshake(Client &client, int udpPort) {
	logInfo(client.getPeer(), "RECV Handshake");

	client.setIsAuthenticated(true);
	client.setUdpPort(udpPort);
}

void	ClientManager::onClientObserveGame(const Client &client, const std::string &name) {
	logInfo(client.getPeer(), "RECV ObserveGame");

	if (client.isAuthenticated() && mListener)
		mListener->onClientObserveGame(client.getPeer(), name);
}

void	ClientManager::onClientLeaveGame(const Client &client) {
	logInfo(client.getPeer(), "RECV LeaveGame");

	if (client.isAuthenticated() && mListener)
		mListener->onClientLeaveGame(client.getPeer());
}

void	ClientManager::onClientUpdatePseudo(Client &client, const std::string &pseudo) {
	logInfo(client.getPeer(), "RECV UpdatePseudo");

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

		if (client != mClients.end()) {
			logInfo((*client)->getPeer(), "SEND Error");
			(*client)->sendError(errorStatus);
		}
	}
}

void	ClientManager::sendShowGame(const std::list<Peer> &peers, const std::string &name, const std::string &levelName, int nbPlayers, int maxPlayers, int nbObservers, int maxObservers) {
	for (const auto &peer : peers) {
		const auto &client = findClient(peer);
			
		if (client != mClients.end()) {
			logInfo((*client)->getPeer(), "SEND ShowGame");
			(*client)->sendShowGame(name, levelName, nbPlayers, maxPlayers, nbObservers, maxObservers);
		}
	}
}

void	ClientManager::sendEndGame(const std::list<Peer> &peers) {
	for (const auto &peer : peers) {
		const auto &client = findClient(peer);

		if (client != mClients.end()) {
			logInfo((*client)->getPeer(), "SEND EndGame");
			(*client)->sendEndGame();
		}
	}
}

void	ClientManager::sendShowLevel(const std::list<Peer> &peers, const std::string &name, const std::string &script) {
	for (const auto &peer : peers) {
		const auto &client = findClient(peer);

		if (client != mClients.end()) {
			logInfo((*client)->getPeer(), "SEND ShowLevel");
			(*client)->sendShowLevel(name, script);
		}
	}
}

std::list<std::shared_ptr<Client>>::iterator ClientManager::findClient(const Peer &peer) {
	return std::find_if(mClients.begin(), mClients.end(), [&](const std::shared_ptr<Client> &client) {
		return client->getPeer() == peer;
	});
}

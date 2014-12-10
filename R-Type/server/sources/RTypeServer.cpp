#include "RTypeServer.hpp"
#include "PortabilityBuilder.hpp"
#include "GamesManagerException.hpp"
#include "PlayerCommunicationManager.hpp"
#include <iostream>

RTypeServer::RTypeServer(void) {
	mClientManager.setListener(this);
	mGamesManager.setListener(this);
}

void RTypeServer::run(void) {
	startInfo();
	mClientManager.run();
	mGamesManager.run();
}

void RTypeServer::startInfo(void) const {
	std::cout << "#######################" << std::endl
			  << "#    R-Type Server    #" << std::endl
		      << "#       Welcome       #" << std::endl
			  << "#######################" << std::endl
			  << std::endl
			  << "Port configuration:" << std::endl
			  << "$> TCP Port: " << ClientManager::SERVER_TCP_PORT << std::endl
			  << "$> UDP Port: " << PlayerCommunicationManager::UDP_PORT << std::endl
			  << std::endl; 
}

void RTypeServer::onEndGame(const std::string &, const std::list<Peer> &gameUsers) {
		mClientManager.sendEndGame(gameUsers);
}

void RTypeServer::onClientDisconnected(const Peer &peer) {
	try {
		mGamesManager.leaveGame(peer);
	}
	catch (const GamesManagerException& ) {
	}
}

void RTypeServer::onClientCreateGame(const Peer &peer, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers) {
	try {
        NGame::Properties properties;

		properties.setName(name);
		properties.setLevelName(levelName);
		properties.setNbMaxPlayers(nbPlayers);
		properties.setNbMaxSpectators(nbObservers);

		mGamesManager.createGame(properties, peer);
		mClientManager.sendError(std::list<Peer>{peer}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<Peer>{peer}, e.getErrorStatus());
	}
}

void RTypeServer::onClientJoinGame(const Peer &peer, const std::string &name, const std::string &pseudo) {
	try {
		mGamesManager.playGame(peer, name, pseudo);
		mClientManager.sendError(std::list<Peer>{peer}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<Peer>{peer}, e.getErrorStatus());
	}
}

void RTypeServer::onClientShowGame(const Peer &peer, const std::string &name) {
	try {
        NGame::Properties properties = mGamesManager.getGameProperties(name);
		mClientManager.sendError(std::list<Peer>{peer}, ErrorStatus(ErrorStatus::Error::OK));
		mClientManager.sendShowGame(std::list<Peer>{peer}, properties.getName(), properties.getLevelName(), properties.getNbPlayers(), properties.getMaxPlayers(), properties.getNbSpectators(), properties.getMaxSpectators());
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<Peer>{peer}, e.getErrorStatus());
	}
}

void RTypeServer::onClientDeleteGame(const Peer &peer, const std::string &name) {
    try {
		mGamesManager.removeGame(peer, name);
		mClientManager.sendError(std::list<Peer>{peer}, ErrorStatus(ErrorStatus::Error::OK));
	}
    catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<Peer>{peer}, e.getErrorStatus());
	}
}

void RTypeServer::onClientListGames(const Peer &peer) {
    std::list<NGame::Properties> games = mGamesManager.getGamesProperties();

	for (const auto &game : games)
		mClientManager.sendShowGame(std::list<Peer>{peer}, game.getName(), game.getLevelName(), game.getNbPlayers(), game.getMaxPlayers(), game.getNbSpectators(), game.getMaxSpectators());
}

void RTypeServer::onClientListLevels(const Peer &peer) {
    auto levels = mGamesManager.getScripts();

    for (const auto &level : levels)
        mClientManager.sendShowLevel(std::list<Peer>{peer}, level.first, level.second);
}

void RTypeServer::onClientObserveGame(const Peer &peer, const std::string &name) {
	try {
		mGamesManager.spectateGame(peer, name);
		mClientManager.sendError(std::list<Peer>{peer}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<Peer>{peer}, e.getErrorStatus());
	}
}

void RTypeServer::onClientLeaveGame(const Peer &peer) {
	try {
		mGamesManager.leaveGame(peer);
		mClientManager.sendError(std::list<Peer>{peer}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<Peer>{peer}, e.getErrorStatus());
	}
}

void RTypeServer::onClientUpdatePseudo(const Peer &peer, const std::string &pseudo) {
	try {
		mGamesManager.updatePseudo(peer, pseudo);
	}
	catch (const GamesManagerException&) {
	}

	mClientManager.sendError(std::list<Peer>{peer}, ErrorStatus(ErrorStatus::Error::OK));
}

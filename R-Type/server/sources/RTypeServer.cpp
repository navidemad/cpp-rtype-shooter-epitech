#include "RTypeServer.hpp"
#include "PortabilityBuilder.hpp"
#include "GamesManagerException.hpp"
#include "PlayerCommunicationManager.hpp"
#include "Default.hpp"
#include <iostream>

RTypeServer::RTypeServer(void) {
	mClientManager.setListener(this);
	mGamesManager.setListener(this);
}

int RTypeServer::run(void) {
	startInfo();
	mClientManager.run();
	return mGamesManager.run();
}

void RTypeServer::startInfo(void) const {
	std::cout << std::endl
		<< "     R-Type Server     " << std::endl
		<< "        Welcome        " << std::endl
		<< std::endl
		<< "  Port TCP | Port UCP  " << std::endl
		<< "    " << Config::Network::tcpPort << "   |   " << Config::Network::udpPort << std::endl
		<< std::endl;
}

void RTypeServer::onEndGame(const std::string &, const std::list<Peer> &gameUsers) {
		mClientManager.sendEndGame(gameUsers);
}

void RTypeServer::onClientDisconnected(const Peer &peer) {
	try {
		mGamesManager.leaveGame(peer);
	}
	catch (const GamesManagerException&) {
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
		std::cout << "[" << __FUNCTION__ << "]: " << e.what() << std::endl; // debug
	}
}

void RTypeServer::onClientJoinGame(const Peer &peer, const std::string &name, const std::string &pseudo) {
	try {
		mGamesManager.playGame(peer, name, pseudo);
		mClientManager.sendError(std::list<Peer>{peer}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<Peer>{peer}, e.getErrorStatus());
		std::cout << "[" << __FUNCTION__ << "]: " << e.what() << std::endl; // debug
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
		std::cout << "[" << __FUNCTION__ << "]: " << e.what() << std::endl; // debug
	}
}

void RTypeServer::onClientDeleteGame(const Peer &peer, const std::string &name) {
    try {
		mGamesManager.removeGame(peer, name);
		mClientManager.sendError(std::list<Peer>{peer}, ErrorStatus(ErrorStatus::Error::OK));
	}
    catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<Peer>{peer}, e.getErrorStatus());
		std::cout << "[" << __FUNCTION__ << "]: " << e.what() << std::endl; // debug
	}
}

void RTypeServer::onClientListGames(const Peer &peer) {
    std::list<NGame::Properties> games = mGamesManager.getGamesProperties();

	for (const auto &game : games)
		mClientManager.sendShowGame(std::list<Peer>{peer}, game.getName(), game.getLevelName(), game.getNbPlayers(), game.getMaxPlayers(), game.getNbSpectators(), game.getMaxSpectators());
}

void RTypeServer::onClientListLevels(const Peer &peer) {
    auto scriptsName = mGamesManager.getScriptsName();

    for (const auto &scriptName : scriptsName)
        mClientManager.sendShowLevel(std::list<Peer>{peer}, scriptName);
}

void RTypeServer::onClientObserveGame(const Peer &peer, const std::string &name) {
	try {
		mGamesManager.spectateGame(peer, name);
		mClientManager.sendError(std::list<Peer>{peer}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<Peer>{peer}, e.getErrorStatus());
		std::cout << "[" << __FUNCTION__ << "]: " << e.what() << std::endl; // debug
	}
}

void RTypeServer::onClientLeaveGame(const Peer &peer) {
	try {
		mGamesManager.leaveGame(peer);
		mClientManager.sendError(std::list<Peer>{peer}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<Peer>{peer}, e.getErrorStatus());
		std::cout << "[" << __FUNCTION__ << "]: " << e.what() << std::endl; // debug
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

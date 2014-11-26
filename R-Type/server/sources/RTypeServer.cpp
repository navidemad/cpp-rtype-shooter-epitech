#include "RTypeServer.hpp"
#include "PortabilityBuilder.hpp"
#include "GamesManagerException.hpp"

RTypeServer::RTypeServer(void) {
	mClientManager.setListener(this);
}

RTypeServer::~RTypeServer(void) {

}

int RTypeServer::run(void) {
	mClientManager.run();
    mGamesManager.run();	
	return 0;
}

void RTypeServer::onClientDisconnected(const std::string &) {
}

void RTypeServer::onClientCreateGame(const std::string &host, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers) {
	try {
		Game::GameProperties properties;

		properties.setName(name);
		properties.setLevelName(levelName);
		properties.setMaxPlayers(nbPlayers);
		properties.setMaxSpectators(nbObservers);

		mGamesManager.createGame(properties, host);
		mClientManager.sendError(std::list<std::string>{host}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<std::string>{host}, e.getErrorStatus());
	}
}

void RTypeServer::onClientJoinGame(const std::string &host, const std::string &name, const std::string &pseudo) {
	try {
		mGamesManager.joinGame(host, name, pseudo);
		mClientManager.sendError(std::list<std::string>{host}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<std::string>{host}, e.getErrorStatus());
	}
}

void RTypeServer::onClientShowGame(const std::string &host, const std::string &name) {
	try {
		Game::GameProperties properties = mGamesManager.getGameProperties(name);
		mClientManager.sendError(std::list<std::string>{host}, ErrorStatus(ErrorStatus::Error::OK));
		mClientManager.sendShowGame(std::list<std::string>{host}, properties.getName(), properties.getLevelName(), properties.getNbPlayers(), properties.getMaxPlayers(), properties.getNbSpectators(), properties.getMaxSpectators());
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<std::string>{host}, e.getErrorStatus());
	}
}

void RTypeServer::onClientDeleteGame(const std::string &host, const std::string &name) {
    try {
		mGamesManager.removeGame(name);
		mClientManager.sendError(std::list<std::string>{host}, ErrorStatus(ErrorStatus::Error::OK));
	}
    catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<std::string>{host}, e.getErrorStatus());
	}
}

void RTypeServer::onClientListGames(const std::string &host) {
	std::list<Game::GameProperties> games = mGamesManager.getGamesProperties();

	for (const auto &game : games)
		mClientManager.sendShowGame(std::list<std::string>{host}, game.getName(), game.getLevelName(), game.getNbPlayers(), game.getMaxPlayers(), game.getNbSpectators(), game.getMaxSpectators());
}

void RTypeServer::onClientListLevels(const std::string &) {
	/* TODO */
}

void RTypeServer::onClientObserveGame(const std::string &host, const std::string &name) {
	try {
		mGamesManager.observeGame(host, name);
		mClientManager.sendError(std::list<std::string>{host}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<std::string>{host}, e.getErrorStatus());
	}
}

void RTypeServer::onClientLeaveGame(const std::string &host) {
	try {
		mGamesManager.leaveGame(host);
		mClientManager.sendError(std::list<std::string>{host}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<std::string>{host}, e.getErrorStatus());
	}
}

void RTypeServer::onClientUpdatePseudo(const std::string &host, const std::string &pseudo) {
	try {
		mGamesManager.updatePseudo(host, pseudo);
		mClientManager.sendError(std::list<std::string>{host}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<std::string>{host}, e.getErrorStatus());
	}
}

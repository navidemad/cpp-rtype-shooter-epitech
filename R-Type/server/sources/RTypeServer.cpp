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
    Game::GameProperties properties;

    properties.setName(name);
    properties.setLevelName(levelName);
    properties.setNbPlayers(nbPlayers);
    properties.setNbSpectators(nbObservers);

	try {
		mGamesManager.createGame(properties, host);
		mClientManager.sendError(std::list<std::string>{host}, ErrorStatus(ErrorStatus::Error::OK));
	}
	catch (const GamesManagerException& e) {
		mClientManager.sendError(std::list<std::string>{host}, e.getErrorStatus());
	}
}

void RTypeServer::onClientJoinGame(const std::string &, const std::string &, const std::string &) {
}

void RTypeServer::onClientShowGame(const std::string &, const std::string &) {
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

void RTypeServer::onClientListGames(const std::string &) {
}

void RTypeServer::onClientListLevels(const std::string &) {
}

void RTypeServer::onClientObserveGame(const std::string &, const std::string &) {
}

void RTypeServer::onClientLeaveGame(const std::string &) {
}

void RTypeServer::onClientUpdatePseudo(const std::string &, const std::string &) {
}

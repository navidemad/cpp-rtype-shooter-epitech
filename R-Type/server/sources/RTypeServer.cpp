#include "RTypeServer.hpp"
#include "PortabilityBuilder.hpp"

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

void RTypeServer::onClientCreateGame(const std::string &, const std::string &, const std::string &, int, int) {
}

void RTypeServer::onClientJoinGame(const std::string &, const std::string &, const std::string &) {
}

void RTypeServer::onClientShowGame(const std::string &, const std::string &) {
}

void RTypeServer::onClientDeleteGame(const std::string &, const std::string &) {
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

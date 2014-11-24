#include "RTypeServer.hpp"
#include "PortabilityBuilder.hpp"

RTypeServer::RTypeServer(void) {

}

RTypeServer::~RTypeServer(void) {

}

int RTypeServer::run(void) {
	mClientManager.run();
    mGamesManager.run();	
	return 0;
}

#include "RTypeServer.hpp"
#include "PortabilityBuilder.hpp"

RTypeServer::RTypeServer(void) {

}

RTypeServer::~RTypeServer(void) {

}

int RTypeServer::run(void) {
	mClientManager.run();
	while (1);//à supprimer. permet de laisser le thread principal tourner pendant que le thread network est lancé.
	
	return 0;
}

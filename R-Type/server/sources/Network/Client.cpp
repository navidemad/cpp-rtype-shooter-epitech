#include "Client.hpp"
#include "CommandUpdateScore.hpp"
Client::Client(const std::shared_ptr<IClientSocket> &client) : mClientPacketBuilder(client) {
	mClientPacketBuilder.registerObserver(ClientPacketBuilder::Event::PACKET_AVAILABLE, std::bind(&Client::onPacketAvailable, this, std::ref(mClientPacketBuilder)));
	mClientPacketBuilder.registerObserver(ClientPacketBuilder::Event::DISCONNECTED, std::bind(&Client::onDisconnection, this, std::ref(mClientPacketBuilder)));
}

Client::~Client(void) {
}

void	Client::onPacketAvailable(const ClientPacketBuilder &) {
}

void	Client::onDisconnection(const ClientPacketBuilder &) {
	mObserver.notifyObservers(Client::Event::DISCONNECTION);
}

void	Client::registerObserver(Client::Event e, const std::function<void()> fct) {
	mObserver.registerObserver(e, fct);
}

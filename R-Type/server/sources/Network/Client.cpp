#include "Client.hpp"

Client::Client(const std::shared_ptr<IClientSocket> &client) : mClientPacketBuilder(client) {
}

Client::~Client(void) {
}

Client::Client(Client &&client) : mClientPacketBuilder(std::move(client.mClientPacketBuilder)) {
}

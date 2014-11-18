#include "UnixPortabilityBuilder.hpp"

std::shared_ptr<IMutex> PortabilityBuilder::getMutex(void) {
	return std::make_shared<UnixMutex>();
}

std::unique_ptr<IClientSocket> PortabilityBuilder::getTcpClient(void) {
	return Utils::make_unique<UnixTcpClient>();
}

std::unique_ptr<IClientSocket> PortabilityBuilder::getUdpClient(void) {
	return Utils::make_unique<UnixUdpClient>();
}

std::unique_ptr<IServerSocket> PortabilityBuilder::getTcpServer(void) {
	return Utils::make_unique<UnixTcpServer>();
}

std::unique_ptr<ICondVar> PortabilityBuilder::getCondVar(void) {
    return Utils::make_unique<UnixCondVar>();
}

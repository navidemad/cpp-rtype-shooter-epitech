#include "PortabilityBuilder.hpp"

std::shared_ptr<IMutex> PortabilityBuilder::getMutex(void) {
	return std::make_shared<WindowsMutex>();
}

std::unique_ptr<IClientSocket> PortabilityBuilder::getTcpClient(void) {
	return Utils::make_unique<WindowsTcpClient>();
}

std::unique_ptr<IClientSocket> PortabilityBuilder::getUdpClient(void) {
	return Utils::make_unique<WindowsUdpClient>();
}

std::unique_ptr<IServerSocket> PortabilityBuilder::getTcpServer(void) {
	return Utils::make_unique<WindowsTcpServer>();
}

std::unique_ptr<ICondVar> PortabilityBuilder::getCondVar(void) {
    return Utils::make_unique<WindowsCondVar>();
}

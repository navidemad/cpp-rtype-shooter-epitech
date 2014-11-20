#include "PortabilityBuilder.hpp"

std::shared_ptr<IMutex> PortabilityBuilder::getMutex(void) {
	return std::make_shared<WindowsMutex>();
}

std::shared_ptr<IClientSocket> PortabilityBuilder::getTcpClient(void) {
	return std::make_shared<WindowsTcpClient>();
}

std::shared_ptr<IClientSocket> PortabilityBuilder::getUdpClient(void) {
	return std::make_shared<WindowsUdpClient>();
}

std::shared_ptr<IServerSocket> PortabilityBuilder::getTcpServer(void) {
	return std::make_shared<WindowsTcpServer>();
}

std::shared_ptr<ICondVar> PortabilityBuilder::getCondVar(void) {
	return std::make_shared<WindowsCondVar>();
}

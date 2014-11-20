#include "UnixPortabilityBuilder.hpp"

# include "UnixMutex.hpp"
# include "UnixTcpClient.hpp"
# include "UnixTcpServer.hpp"
# include "UnixUdpClient.hpp"
# include "UnixCondVar.hpp"

std::shared_ptr<IMutex> PortabilityBuilder::getMutex(void) {
	return std::make_shared<UnixMutex>();
}

std::shared_ptr<IClientSocket> PortabilityBuilder::getTcpClient(void) {
	return std::make_shared<UnixTcpClient>();
}

std::shared_ptr<IClientSocket> PortabilityBuilder::getUdpClient(void) {
	return std::make_shared<UnixUdpClient>();
}

std::shared_ptr<IServerSocket> PortabilityBuilder::getTcpServer(void) {
	return std::make_shared<UnixTcpServer>();
}

std::shared_ptr<ICondVar> PortabilityBuilder::getCondVar(void) {
    return std::make_shared<UnixCondVar>();
}

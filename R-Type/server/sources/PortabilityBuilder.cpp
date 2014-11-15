#include "PortabilityBuilder.hpp"

std::shared_ptr<IMutex> PortabilityBuilder::getMutex(void) {
#ifdef __unix__
	return std::make_shared<UnixMutex>();
#elif defined(_WIN32) || defined(WIN32)
	return std::make_shared<WindowsMutex>();
#endif
}

std::shared_ptr<IClientSocket> PortabilityBuilder::getTcpClient(void) {
#ifdef __unix__
	return std::make_shared<UnixTcpClient>();
#elif defined(_WIN32) || defined(WIN32)
	return std::make_shared<WindowsTcpClient>();
#endif
}

std::shared_ptr<IClientSocket> PortabilityBuilder::getUdpClient(void) {
#ifdef __unix__
	return std::make_shared<UnixUdpClient>();
#elif defined(_WIN32) || defined(WIN32)
	return std::make_shared<WindowsUdpClient>();
#endif
}

std::shared_ptr<IServerSocket> PortabilityBuilder::getTcpServer(void) {
#ifdef __unix__
	return std::make_shared<UnixTcpServer>();
#elif defined(_WIN32) || defined(WIN32)
	return std::make_shared<WindowsTcpServer>();
#endif
}

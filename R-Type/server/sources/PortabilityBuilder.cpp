#include "PortabilityBuilder.hpp"

std::shared_ptr<IMutex> PortabilityBuilder::getMutex(void) {
#ifdef __unix__
	return std::shared_ptr<IMutex>(new UnixMutex);
#elif defined(_WIN32) || defined(WIN32)
	return std::shared_ptr<IMutex>(new WindowMutex);
#endif
}

std::shared_ptr<IClientSocket> PortabilityBuilder::getTcpClient(void) {
#ifdef __unix__
	return std::shared_ptr<IClientSocket>(new UnixTcpClient);
#elif defined(_WIN32) || defined(WIN32)
	return std::shared_ptr<IClientSocket>(new WindowsTcpClient);
#endif
}

std::shared_ptr<IClientSocket> PortabilityBuilder::getUdpClient(void) {
#ifdef __unix__
	return std::shared_ptr<IClientSocket>(new UnixUdpClient);
#elif defined(_WIN32) || defined(WIN32)
	return std::shared_ptr<IClientSocket>(new WindowsUdpClient);
#endif
}

std::shared_ptr<IServerSocket> PortabilityBuilder::getTcpServer(void) {
#ifdef __unix__
	return std::shared_ptr<IServerSocket>(new UnixTcpServer);
#elif defined(_WIN32) || defined(WIN32)
	return std::shared_ptr<IServerSocket>(new WindowsTcpServer);
#endif
}

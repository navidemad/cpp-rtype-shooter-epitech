#include "WindowsTcpServer.hpp"

WindowsTcpServer::WindowsTcpServer(void) {
}

WindowsTcpServer::~WindowsTcpServer(void) {
}

void	WindowsTcpServer::createServer(int, int) {
}

void	WindowsTcpServer::closeServer(void) {
}

void	WindowsTcpServer::setOnSocketEventListener(IServerSocket::OnSocketEvent *) {
}

std::shared_ptr<IClientSocket>	WindowsTcpServer::getNewClient(void) {
	return shared_ptr<IClientSocket>(nullptr);
}

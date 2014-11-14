#include "WindowsTcpClient.hpp"

WindowsTcpClient::WindowsTcpClient(void) {
}

WindowsTcpClient::~WindowsTcpClient(void) {
}

void	WindowsTcpClient::connect(const std::string &, int) {
}

void	WindowsTcpClient::initFromSocket(void *, const std::string &, int) {
}

void	WindowsTcpClient::closeClient(void) {
}

void	WindowsTcpClient::send(const IClientSocket::Message &) {
}

IClientSocket::Message	WindowsTcpClient::receive(unsigned int) {
	return IClientSocket::Message();
}

unsigned int	WindowsTcpClient::nbBytesToRead(void) const {
	return 0;
}

const std::string &WindowsTcpClient::getAddr(void) const {
	/* LOL */
	std::string *ptr = new std::string;
	return *ptr;
}

void	WindowsTcpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *) {
}

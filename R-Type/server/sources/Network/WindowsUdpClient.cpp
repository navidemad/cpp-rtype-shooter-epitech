#include "WindowsUdpClient.hpp"

WindowsUdpClient::WindowsUdpClient(void) {
}

WindowsUdpClient::~WindowsUdpClient(void) {
}

void	WindowsUdpClient::connect(const std::string &, int) {
}

void	WindowsUdpClient::initFromSocket(void *, const std::string &, int) {
}

void	WindowsUdpClient::closeClient(void) {
}

void	WindowsUdpClient::send(const IClientSocket::Message &) {
}

IClientSocket::Message	WindowsUdpClient::receive(unsigned int) {
	return IClientSocket::Message();
}

unsigned int	WindowsUdpClient::nbBytesToRead(void) const {
	return 0;
}

const std::string &WindowsUdpClient::getAddr(void) const {
	/* LOL */
	std::string *ptr = new std::string;
	return *ptr;
}

void	WindowsUdpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *) {
}

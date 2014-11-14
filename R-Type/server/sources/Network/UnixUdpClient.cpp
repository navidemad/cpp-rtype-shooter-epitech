#include "UnixUdpClient.hpp"

UnixUdpClient::UnixUdpClient(void) {
}

UnixUdpClient::~UnixUdpClient(void) {
}

void	UnixUdpClient::connect(const std::string &, int) {
}

void	UnixUdpClient::initFromSocket(void *, const std::string &, int) {
}

void	UnixUdpClient::closeClient(void) {
}

void	UnixUdpClient::send(const IClientSocket::Message &) {
}

IClientSocket::Message	UnixUdpClient::receive(unsigned int) {
	return IClientSocket::Message();
}

unsigned int	UnixUdpClient::nbBytesToRead(void) const {
	return 0;
}

const std::string &UnixUdpClient::getAddr(void) const {
	/* LOL */
	std::string *ptr = new std::string;
	return *ptr;
}

void	UnixUdpClient::setOnSocketEventListener(IClientSocket::OnSocketEvent *) {
}

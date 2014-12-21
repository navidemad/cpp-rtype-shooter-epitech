#pragma once

#include <string>

struct Peer {
	Peer(const std::string &pHost = "", int pTcpPort = -1, int pUdpPort = -1) : host(pHost), tcpPort(pTcpPort), udpPort(pUdpPort) {}

	std::string	host;
	int					tcpPort;
	int					udpPort;

	bool operator==(const Peer &peer) const {
		if (host != peer.host)
			return false;

		if (tcpPort != -1 && peer.tcpPort != -1 && tcpPort != peer.tcpPort)
			return false;

		if (udpPort != -1 && peer.udpPort != -1 && udpPort != peer.udpPort)
			return false;

		return true;
	}

	bool operator!=(const Peer &peer) const {
	    return !(*this == peer);
	}

};

#pragma once

#include <string>

struct Peer {
	std::string	host;
	int					port;

	bool operator==(const Peer &peer) const {
		return host == peer.host && port == peer.port;
	}
};
#pragma once

#include <memory>
#include "IClientSocket.hpp"
#include "ClientPacketBuilder.hpp"

class Client {

	// ctor dtor
	public:
		explicit Client(const std::shared_ptr<IClientSocket> &client);
		~Client(void);

	// copy operators
	public:
		Client(const Client &) = delete;
		Client(Client &&);
		const Client &operator=(const Client &) = delete;
		const Client &operator=(Client &&) = delete;

	// attributes
	private:
		ClientPacketBuilder mClientPacketBuilder;

};

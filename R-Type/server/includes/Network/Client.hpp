#pragma once

#include <memory>
#include "Observer.hpp"
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
		Client(Client &&) = delete;
		const Client &operator=(const Client &) = delete;
		const Client &operator=(Client &&) = delete;

	// events
	public:
		enum class Event {
			DISCONNECTION
		};

		void	registerObserver(Client::Event e, const std::function<void()> fct);
		void	onPacketAvailable(const ClientPacketBuilder &clientPacketBuilder);
		void	onDisconnection(const ClientPacketBuilder &clientPacketBuilder);

	// attributes
	private:
		Observer<Client::Event> mObserver;
		ClientPacketBuilder mClientPacketBuilder;

};

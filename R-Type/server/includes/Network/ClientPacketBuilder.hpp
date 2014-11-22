#pragma once

#include <memory>
#include "ICommand.hpp"
#include "Observer.hpp"
#include "IClientSocket.hpp"

class ClientPacketBuilder : public IClientSocket::OnSocketEvent {

	// ctor dtor
	public:
		explicit ClientPacketBuilder(const std::shared_ptr<IClientSocket> &client);
		~ClientPacketBuilder(void);

	// copy move operators
	public:
		ClientPacketBuilder(const ClientPacketBuilder &) = delete;
		ClientPacketBuilder(ClientPacketBuilder &&);
		const ClientPacketBuilder &operator=(const ClientPacketBuilder &) = delete;
		const ClientPacketBuilder &operator=(ClientPacketBuilder &&) = delete;

	// interface implementation
	public:
		void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes);
		void	onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
		void	onSocketClosed(IClientSocket *socket);

	// events
	public:
		enum class Event {
			PACKET_AVAILABLE,
			DISCONNECTED
		};

		void	registerObserver(ClientPacketBuilder::Event e, const std::function<void()> &fct);

		// handle build state
	private:
		enum class State {
			HEADER,
			BODY
		};

	void	fetchHeader(void);
	void	fetchBody(void);

	// attributes
	private:
		State mState;
		std::shared_ptr<ICommand> mCurrentCommand;
		Observer<Event> mObserver;
		std::shared_ptr<IClientSocket>	mClient;

};

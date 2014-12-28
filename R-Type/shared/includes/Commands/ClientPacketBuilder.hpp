#pragma once

#include "ICommand.hpp"
#include "IClientSocket.hpp"
#include "NoCopyable.hpp"

#include <memory>

class ClientPacketBuilder : public NoCopyable, public IClientSocket::OnSocketEvent {

	// ctor dtor
	public:
		explicit ClientPacketBuilder(const std::shared_ptr<IClientSocket> &client);
		~ClientPacketBuilder(void);

	// interface implementation
	public:
		void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes);
		void	onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
		void	onSocketClosed(IClientSocket *socket);

	// events
	public:
		class OnClientPacketBuilderEvent {
			public:
                virtual ~OnClientPacketBuilderEvent(void) = default;
				virtual void	onPacketAvailable(const ClientPacketBuilder &clientPacketBuilder, const std::shared_ptr<ICommand> &command) = 0;
				virtual void	onSocketClosed(const ClientPacketBuilder &clientPacketBuilder) = 0;
		};

		void	setListener(ClientPacketBuilder::OnClientPacketBuilderEvent *listener);

	// handle commands
	public:
		void	sendCommand(const ICommand *command);
		const	std::shared_ptr<ICommand> &getCommand(void) const;

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
		ClientPacketBuilder::OnClientPacketBuilderEvent *mListener;
		std::shared_ptr<IClientSocket>	mClient;

};

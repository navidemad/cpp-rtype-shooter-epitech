#pragma once

#include "IClientSocket.hpp"
#include "ICommand.hpp"
#include "Peer.hpp"
#include "NoCopyable.hpp"

#include <memory>
#include <deque>

class PlayerPacketBuilder : public NoCopyable, public IClientSocket::OnSocketEvent {

	// ctor dtor
	public:
		explicit PlayerPacketBuilder(int port);
		~PlayerPacketBuilder(void);

	// handle build state
	private:
		enum class State {
			HEADER,
			BODY
		};

		void	fetchHeader(void);
		void	fetchBody(void);

	// events
	public:
		class OnPlayerPacketBuilderEvent {
			public:
				virtual ~OnPlayerPacketBuilderEvent(void) {}
				virtual void onPacketAvailable(const PlayerPacketBuilder &clientPacketBuilder, const std::shared_ptr<ICommand> &command, const Peer &peer) = 0;
		};

		void	setListener(PlayerPacketBuilder::OnPlayerPacketBuilderEvent *listener);

		void	onBytesWritten(IClientSocket *socket, unsigned int nbBytes);
		void	onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
		void	onSocketClosed(IClientSocket *socket);

	// internal methods
	private:
		void	fetchPackets(void);
		void	mergeWithLastDatagram(const IClientSocket::Message &message);
		void	cleanDatagramsList(unsigned int sizeToRead);
		IClientSocket::Message getPartOfFirstDatagram(unsigned int sizeToRead);

	// send commands
	public:
		void	sendCommand(const ICommand *command, const Peer &peer);

	// attributes
	private:
		std::string mCurrentHost;
		int mCurrentPort;
		PlayerPacketBuilder::State mCurrentState;
		std::shared_ptr<ICommand> mCurrentCommand;
		std::shared_ptr<IClientSocket> mClient;
		std::deque<IClientSocket::Message> mDatagrams;
		PlayerPacketBuilder::OnPlayerPacketBuilderEvent *mListener;

};

#pragma once

#include "PlayerPacketBuilder.hpp"
#include "IMutex.hpp"
#include "IResource.hpp"
#include <list>

class PlayerCommunicationManager : public PlayerPacketBuilder::OnPlayerPacketBuilderEvent {

	// ctor dtor
	public:
		PlayerCommunicationManager(void);
		~PlayerCommunicationManager(void);

	// move copy operators
	private:
		PlayerCommunicationManager(const PlayerCommunicationManager &) = delete;
		PlayerCommunicationManager(PlayerCommunicationManager &&) = delete;
		const PlayerCommunicationManager &operator=(const PlayerCommunicationManager &) = delete;
		const PlayerCommunicationManager &operator=(PlayerCommunicationManager &&) = delete;

	// peer
	private:
		struct Peer {
			std::string host;
			int port;
		};

		std::list<PlayerCommunicationManager::Peer>::iterator findPeer(const std::string &host, int port);

	public:
		void	addPeerToWhiteList(const std::string &host, int port);
		void	removePeerFromWhiteList(const std::string &host, int port);

	// events
	public:
		class OnPlayerCommunicationManagerEvent {
		public:
			virtual ~OnPlayerCommunicationManagerEvent(void) {}
			virtual void onPlayerFire(const PlayerCommunicationManager &playerCommunicationManager, const std::string &host, int port) = 0;
			virtual void onPlayerMove(const PlayerCommunicationManager &playerCommunicationManager, IResource::Direction direction, const std::string &host, int port) = 0;
		};

		void	setListener(PlayerCommunicationManager::OnPlayerCommunicationManagerEvent *listener);

		void	onPacketAvailable(const PlayerPacketBuilder &clientPacketBuilder, const std::shared_ptr<ICommand> &command, const std::string &host, int port);

	// build cmd
	private:
		struct CommandExec {
			ICommand::Instruction	instruction;
			void					(PlayerCommunicationManager::*ftPtr)(const std::shared_ptr<ICommand> &command, const PlayerCommunicationManager::Peer &peer);
		};

		static const PlayerCommunicationManager::CommandExec commandExecTab[];

		void	recvMove(const std::shared_ptr<ICommand> &command, const PlayerCommunicationManager::Peer &peer);
		void	recvFire(const std::shared_ptr<ICommand> &command, const PlayerCommunicationManager::Peer &peer);

	// attributes
	private:
		PlayerPacketBuilder mPlayerPacketBuilder;
		std::list<PlayerCommunicationManager::Peer> mAllowedPeers;
		std::shared_ptr<IMutex> mMutex;
		PlayerCommunicationManager::OnPlayerCommunicationManagerEvent *mListener;

		static const int UDP_PORT = 4242;

};
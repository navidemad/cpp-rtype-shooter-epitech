#pragma once

#include "Peer.hpp"
#include "PlayerPacketBuilder.hpp"
#include "IMutex.hpp"
#include "IResource.hpp"
#include "NoCopyable.hpp"

#include <list>

class PlayerCommunicationManager : public NoCopyable, public PlayerPacketBuilder::OnPlayerPacketBuilderEvent {

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

	// internal methods
	private:
		std::list<Peer>::iterator findPeer(const Peer &peer);
		void logInfo(const Peer &peer, const std::string &log) const;

	public:
		void	addPeerToWhiteList(const Peer &peer);
		void	removePeerFromWhiteList(const Peer &peer);

	// events
	public:
		class OnPlayerCommunicationManagerEvent {
		public:
			virtual ~OnPlayerCommunicationManagerEvent(void) {}
			virtual void onPlayerFire(PlayerCommunicationManager &playerCommunicationManager, const Peer &peer) = 0;
			virtual void onPlayerMove(PlayerCommunicationManager &playerCommunicationManager, IResource::Direction direction, const Peer &peer) = 0;
		};

		void	setListener(PlayerCommunicationManager::OnPlayerCommunicationManagerEvent *listener);

		void	onPacketAvailable(const PlayerPacketBuilder &clientPacketBuilder, const std::shared_ptr<ICommand> &command, const Peer &peer);

	// send commands
	public:
		void	sendMoveResource(const Peer &peer, uint64_t id, IResource::Type type, double x, double y, short angle);
		void	sendDestroyResource(const Peer &peer, uint64_t id);
		void	sendUpdateScore(const Peer &peer, uint64_t id, const std::string &pseudo, uint64_t score);
		void	sendTimeElapsedPing(const Peer &peer, double timeElapsed);

	// build cmd
	private:
		struct CommandExec {
			ICommand::Instruction	instruction;
			void					(PlayerCommunicationManager::*ftPtr)(const std::shared_ptr<ICommand> &command, const Peer &peer);
		};

		static const PlayerCommunicationManager::CommandExec commandExecTab[];

		void	recvMove(const std::shared_ptr<ICommand> &command, const Peer &peer);
		void	recvFire(const std::shared_ptr<ICommand> &command, const Peer &peer);

	// attributes
	private:
		PlayerPacketBuilder mPlayerPacketBuilder;
		std::list<Peer> mAllowedPeers;
		std::shared_ptr<IMutex> mMutex;
		PlayerCommunicationManager::OnPlayerCommunicationManagerEvent *mListener;

	public:
		static const int UDP_PORT = 4243;

};

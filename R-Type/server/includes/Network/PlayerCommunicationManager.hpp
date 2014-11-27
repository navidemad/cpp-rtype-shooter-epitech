#pragma once

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

	// send commands
	public:
		void	sendMoveResource(const std::string &host, int port, int id, IResource::Type type, float x, float y, short angle);
		void	sendDestroyResource(const std::string &host, int port, int id);
		void	sendUpdateScore(const std::string &host, int port, int id, const std::string &pseudo, int score);
		void	sendTimeElapsedPing(const std::string &host, int port, int64_t timeElapsed);

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

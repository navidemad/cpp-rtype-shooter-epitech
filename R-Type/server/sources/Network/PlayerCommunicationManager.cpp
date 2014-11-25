#include "PlayerCommunicationManager.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include "CommandMove.hpp"
#include <algorithm>

const PlayerCommunicationManager::CommandExec PlayerCommunicationManager::commandExecTab[] = {
	{ ICommand::Instruction::MOVE, &PlayerCommunicationManager::recvMove },
	{ ICommand::Instruction::FIRE, &PlayerCommunicationManager::recvFire }
};

PlayerCommunicationManager::PlayerCommunicationManager(void) : mPlayerPacketBuilder(PlayerCommunicationManager::UDP_PORT), mMutex(PortabilityBuilder::getMutex()), mListener(nullptr) {
	mPlayerPacketBuilder.setListener(this);
}

PlayerCommunicationManager::~PlayerCommunicationManager(void) {
}

void PlayerCommunicationManager::onPacketAvailable(const PlayerPacketBuilder &, const std::shared_ptr<ICommand> &command, const std::string &host, int port) {

	PlayerCommunicationManager::Peer peer;
	{
		ScopedLock scopedLock(mMutex);

		const auto &peerIt = findPeer(host, port);
		if (peerIt == mAllowedPeers.end())
			return;

		peer = *peerIt;
	}

	for (const auto &instr : commandExecTab)
		if (instr.instruction == command->getInstruction()) {
			(this->*instr.ftPtr)(command, peer);
			return;
		}
}

void	PlayerCommunicationManager::recvMove(const std::shared_ptr<ICommand> &command, const PlayerCommunicationManager::Peer &peer) {
	if (mListener) {
		std::shared_ptr<CommandMove> commandMove = std::static_pointer_cast<CommandMove>(command);

		mListener->onPlayerMove(*this, commandMove->getDirection(), peer.host, peer.port);
	}
}

void	PlayerCommunicationManager::recvFire(const std::shared_ptr<ICommand> &, const PlayerCommunicationManager::Peer &peer) {
	if (mListener)
		mListener->onPlayerFire(*this, peer.host, peer.port);
}

void PlayerCommunicationManager::addPeerToWhiteList(const std::string &host, int port) {
	ScopedLock scopedLock(mMutex);

	if (findPeer(host, port) == mAllowedPeers.end())
		mAllowedPeers.push_back(Peer{ host, port });
}

void PlayerCommunicationManager::removePeerFromWhiteList(const std::string &host, int port) {
	ScopedLock scopedLock(mMutex);

	const auto &peer = findPeer(host, port);
	if (peer != mAllowedPeers.end())
		mAllowedPeers.erase(peer);
}

std::list<PlayerCommunicationManager::Peer>::iterator PlayerCommunicationManager::findPeer(const std::string &host, int port) {
	return std::find_if(mAllowedPeers.begin(), mAllowedPeers.end(), [&](const PlayerCommunicationManager::Peer &peer) { return peer.host == host && peer.port == port; });
}

void PlayerCommunicationManager::setListener(PlayerCommunicationManager::OnPlayerCommunicationManagerEvent *listener) {
	mListener = listener;
}

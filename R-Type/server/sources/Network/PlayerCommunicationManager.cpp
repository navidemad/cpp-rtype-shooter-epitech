#include "PlayerCommunicationManager.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include "CommandMove.hpp"
#include "CommandMoveResource.hpp"
#include "CommandDestroyResource.hpp"
#include "CommandUpdateScore.hpp"
#include "CommandTimeElapsedPing.hpp"
#include <algorithm>
#include <iostream>

const PlayerCommunicationManager::CommandExec PlayerCommunicationManager::commandExecTab[] = {
	{ ICommand::Instruction::MOVE, &PlayerCommunicationManager::recvMove },
	{ ICommand::Instruction::FIRE, &PlayerCommunicationManager::recvFire }
};

PlayerCommunicationManager::PlayerCommunicationManager(void) : 
mPlayerPacketBuilder(PlayerCommunicationManager::UDP_PORT),
mMutex(PortabilityBuilder::getMutex()),
mListener(nullptr) {
	mPlayerPacketBuilder.setListener(this);
}

PlayerCommunicationManager::~PlayerCommunicationManager(void) {

}

void PlayerCommunicationManager::onPacketAvailable(const PlayerPacketBuilder &, const std::shared_ptr<ICommand> &command, const Peer &peer) {
  std::cout << "PACKET AVAILABLE" << std::endl;
  std::cout << "peer>" << peer.host << "@" << peer.port << std::endl;
	{
		ScopedLock scopedLock(mMutex);
		std::cout << "lock" << std::endl;
		if (findPeer(peer) == mAllowedPeers.end())
			return;
		std::cout << "find" << std::endl;
	}

	for (const auto &instr : commandExecTab)
		if (instr.instruction == command->getInstruction()) {
			(this->*instr.ftPtr)(command, peer);
			return;
		}
}

void	PlayerCommunicationManager::recvMove(const std::shared_ptr<ICommand> &command, const Peer &peer) {
  std::cout << "recv move" << std::endl;

	if (mListener) {
		std::shared_ptr<CommandMove> commandMove = std::static_pointer_cast<CommandMove>(command);

		mListener->onPlayerMove(*this, commandMove->getDirection(), peer);
	}
}

void	PlayerCommunicationManager::recvFire(const std::shared_ptr<ICommand> &, const Peer &peer) {
  std::cout << "recv fire" << std::endl;

	if (mListener)
		mListener->onPlayerFire(*this, peer);
}

void PlayerCommunicationManager::addPeerToWhiteList(const Peer &peer) {
	ScopedLock scopedLock(mMutex);

	if (findPeer(peer) == mAllowedPeers.end())
		mAllowedPeers.push_back(peer);
}

void PlayerCommunicationManager::removePeerFromWhiteList(const Peer &peer) {
	ScopedLock scopedLock(mMutex);

	const auto &peerIt = findPeer(peer);
	if (peerIt != mAllowedPeers.end())
		mAllowedPeers.erase(peerIt);
}
#include <iostream>
std::list<Peer>::iterator PlayerCommunicationManager::findPeer(const Peer &peer) {
  return std::find_if(mAllowedPeers.begin(), mAllowedPeers.end(), [&](const Peer &peerIt) { 
      std::cout << peer.host << "@" << peer.port << std::endl;
      std::cout << peerIt.host << "@" << peerIt.port << std::endl;
      return peer == peerIt;
    });
}

void PlayerCommunicationManager::setListener(PlayerCommunicationManager::OnPlayerCommunicationManagerEvent *listener) {
	mListener = listener;
}

void PlayerCommunicationManager::sendMoveResource(const Peer &peer, int id, IResource::Type type, float x, float y, short angle) {
	CommandMoveResource commandMoveResource;

	commandMoveResource.setId(id);
	commandMoveResource.setType(type);
	commandMoveResource.setX(x);
	commandMoveResource.setY(y);
	commandMoveResource.setAngle(angle);
	mPlayerPacketBuilder.sendCommand(&commandMoveResource, peer);
}

void PlayerCommunicationManager::sendDestroyResource(const Peer &peer, int id) {
	CommandDestroyResource commandDestroyResource;

	commandDestroyResource.setId(id);
	mPlayerPacketBuilder.sendCommand(&commandDestroyResource, peer);
}

void PlayerCommunicationManager::sendUpdateScore(const Peer &peer, int id, const std::string &pseudo, int score) {
	CommandUpdateScore commandUpdateScore;

	commandUpdateScore.setId(id);
	commandUpdateScore.setPseudo(pseudo);
	commandUpdateScore.setScore(score);
	mPlayerPacketBuilder.sendCommand(&commandUpdateScore, peer);
}

void PlayerCommunicationManager::sendTimeElapsedPing(const Peer &peer, int64_t timeElapsed) {
	CommandTimeElapsedPing commandTimeElapsedPing;

	commandTimeElapsedPing.setTimeElapsed(timeElapsed);
	mPlayerPacketBuilder.sendCommand(&commandTimeElapsedPing, peer);
}

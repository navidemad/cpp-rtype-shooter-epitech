#include "PlayerCommunicationManager.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"
#include "CommandMove.hpp"
#include "CommandMoveResource.hpp"
#include "CommandDestroyResource.hpp"
#include "CommandUpdateScore.hpp"
#include "CommandTimeElapsedPing.hpp"
#include <algorithm>
#include "Utils.hpp"
#include "Default.hpp"

const PlayerCommunicationManager::CommandExec PlayerCommunicationManager::commandExecTab[] = {
	{ ICommand::Instruction::MOVE, &PlayerCommunicationManager::recvMove },
	{ ICommand::Instruction::FIRE, &PlayerCommunicationManager::recvFire }
};

PlayerCommunicationManager::PlayerCommunicationManager(void) : 
mPlayerPacketBuilder(Config::Network::udpPort),
mMutex(PortabilityBuilder::getMutex()),
mListener(nullptr) {
	mPlayerPacketBuilder.setListener(this);
}

PlayerCommunicationManager::~PlayerCommunicationManager(void) {

}

void PlayerCommunicationManager::logInfo(const Peer &peer, const std::string &log) const {
	std::stringstream ss;

	ss << Utils::RED << "[UDP]" << Utils::YELLOW << "[" << peer.host << ":" << peer.udpPort << "]> " << Utils::WHITE << log; 
	Utils::logInfo(ss.str());
}

void PlayerCommunicationManager::onPacketAvailable(const PlayerPacketBuilder &, const std::shared_ptr<ICommand> &command, const Peer &peer) {
	{
		Scopedlock(mMutex);

		if (findPeer(peer) == mAllowedPeers.end()) {
		  logInfo(peer, "Not whitelisted - Not treated");
			return;
		}
		else
		  logInfo(peer, "Whitelisted - Treated");
	}

	for (const auto &instr : commandExecTab)
		if (instr.instruction == command->getInstruction()) {
			(this->*instr.ftPtr)(command, peer);
			return;
		}
}

void	PlayerCommunicationManager::recvMove(const std::shared_ptr<ICommand> &command, const Peer &peer) {
  logInfo(peer, "RECV move");

	if (mListener) {
		std::shared_ptr<CommandMove> commandMove = std::static_pointer_cast<CommandMove>(command);

		mListener->onPlayerMove(commandMove->getDirection(), peer);
	}
}

void	PlayerCommunicationManager::recvFire(const std::shared_ptr<ICommand> &, const Peer &peer) {
  logInfo(peer, "RECV fire");

	if (mListener)
		mListener->onPlayerFire(peer);
}

void PlayerCommunicationManager::addPeerToWhiteList(const Peer &peer) {
	Scopedlock(mMutex);

	if (findPeer(peer) == mAllowedPeers.end())
		mAllowedPeers.push_back(peer);
}

void PlayerCommunicationManager::removePeerFromWhiteList(const Peer &peer) {
	Scopedlock(mMutex);

	const auto &peerIt = findPeer(peer);
	if (peerIt != mAllowedPeers.end())
		mAllowedPeers.erase(peerIt);
}

std::list<Peer>::iterator PlayerCommunicationManager::findPeer(const Peer &peer) {
  return std::find_if(mAllowedPeers.begin(), mAllowedPeers.end(), [&](const Peer &peerIt) { 
      return peer == peerIt;
    });
}

void PlayerCommunicationManager::setListener(PlayerCommunicationManager::OnPlayerCommunicationManagerEvent *listener) {
	mListener = listener;
}

void PlayerCommunicationManager::sendMoveResource(const Peer &peer, uint64_t id, IResource::Type type, double x, double y, short angle) {
	logInfo(peer, "SEND sendMoveResource " + Utils::toString<uint64_t>(id));
	CommandMoveResource commandMoveResource;

	commandMoveResource.setId(id);
	commandMoveResource.setType(type);
	commandMoveResource.setX(x);
	commandMoveResource.setY(y);
	commandMoveResource.setAngle(angle);
	mPlayerPacketBuilder.sendCommand(&commandMoveResource, peer);
}

void PlayerCommunicationManager::sendDestroyResource(const Peer &peer, uint64_t id) {
	logInfo(peer, "SEND sendDestroyResource " + Utils::toString<uint64_t>(id));
	CommandDestroyResource commandDestroyResource;

	commandDestroyResource.setId(id);
	mPlayerPacketBuilder.sendCommand(&commandDestroyResource, peer);
}

void PlayerCommunicationManager::sendUpdateScore(const Peer &peer, uint64_t id, const std::string &pseudo, uint64_t score) {
	logInfo(peer, "SEND sendUpdateScore " + Utils::toString<uint64_t>(score));
	CommandUpdateScore commandUpdateScore;

	commandUpdateScore.setId(id);
	commandUpdateScore.setPseudo(pseudo);
	commandUpdateScore.setScore(score);
	mPlayerPacketBuilder.sendCommand(&commandUpdateScore, peer);
}

void PlayerCommunicationManager::sendTimeElapsedPing(const Peer &peer, double timeElapsed) {
	logInfo(peer, "SEND sendTimeElapsedPing " + Utils::toString<double>(timeElapsed));
	CommandTimeElapsedPing commandTimeElapsedPing;

	commandTimeElapsedPing.setTimeElapsed(timeElapsed);
	mPlayerPacketBuilder.sendCommand(&commandTimeElapsedPing, peer);
}

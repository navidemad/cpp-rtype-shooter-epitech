#include "Client.hpp"
#include "CommandCreateGame.hpp"
#include "CommandJoinGame.hpp"
#include "CommandShowGame.hpp"
#include "CommandDeleteGame.hpp"
#include "CommandListGames.hpp"
#include "CommandListLevels.hpp"
#include "CommandObserveGame.hpp"
#include "CommandHandshake.hpp"
#include "CommandLeaveGame.hpp"
#include "CommandUpdatePseudo.hpp"
#include "CommandError.hpp"
#include "CommandEndGame.hpp"
#include "CommandShowLevel.hpp"
#include "ErrorStatus.hpp"
#include "Utils.hpp"

const Client::CommandExec Client::commandExecTab[] = {
	{ ICommand::Instruction::CREATE_GAME, &Client::recvCreateGame },
	{ ICommand::Instruction::JOIN_GAME, &Client::recvJoinGame },
	{ ICommand::Instruction::SHOW_GAME, &Client::recvShowGame },
	{ ICommand::Instruction::DELETE_GAME, &Client::recvDeleteGame },
	{ ICommand::Instruction::LIST_GAMES, &Client::recvListGames },
	{ ICommand::Instruction::LIST_LEVELS, &Client::recvListLevels },
	{ ICommand::Instruction::HANDSHAKE, &Client::recvHandshake },
	{ ICommand::Instruction::OBSERVE_GAME, &Client::recvObserveGame },
	{ ICommand::Instruction::LEAVE_GAME, &Client::recvLeaveGame },
	{ ICommand::Instruction::UPDATE_PSEUDO, &Client::recvUpdatePseudo }
};

Client::Client(const std::shared_ptr<IClientSocket> &client)
: mPeer(client->getAddr(), client->getPort()), mPseudo(""), mIsAuthenticated(false), mListener(nullptr), mClientPacketBuilder(client)
{
	mClientPacketBuilder.setListener(this);
}

Client::~Client(void) {
}

void	Client::onPacketAvailable(const ClientPacketBuilder &, const std::shared_ptr<ICommand> &command) {
	for (const auto &cmdExec : commandExecTab)
	if (cmdExec.instruction == command->getInstruction()) {
		(this->*cmdExec.ftPtr)(command);
		return;
	}
}

void	Client::onSocketClosed(const ClientPacketBuilder &) {
	if (mListener){
		mListener->onClientDisconnected(*this);
	}
}

void	Client::setListener(Client::OnClientEvent *listener) {
	mListener = listener;
}

void	Client::recvCreateGame(const std::shared_ptr<ICommand> &command) {
	if (mListener) {
		const std::shared_ptr<CommandCreateGame> commandCreateGame = std::static_pointer_cast<CommandCreateGame>(command);

		mListener->onClientCreateGame(*this,
			commandCreateGame->getName(),
			commandCreateGame->getLevelName(),
			commandCreateGame->getNbPlayers(),
			commandCreateGame->getNbSpectators());
	}
}

void	Client::recvJoinGame(const std::shared_ptr<ICommand> &command) {
	if (mListener) {
		const std::shared_ptr<CommandJoinGame> commandJoinGame = std::static_pointer_cast<CommandJoinGame>(command);

		mListener->onClientJoinGame(*this, commandJoinGame->getName());
	}
}

void	Client::recvShowGame(const std::shared_ptr<ICommand> &command) {
	if (mListener) {
		const std::shared_ptr<CommandShowGame> commandShowGame = std::static_pointer_cast<CommandShowGame>(command);

		mListener->onClientShowGame(*this, commandShowGame->getName());
	}
}

void	Client::recvDeleteGame(const std::shared_ptr<ICommand> &command) {
	if (mListener) {
		const std::shared_ptr<CommandDeleteGame> commandDeleteGame = std::static_pointer_cast<CommandDeleteGame>(command);

		mListener->onClientDeleteGame(*this, commandDeleteGame->getName());
	}
}

void	Client::recvListGames(const std::shared_ptr<ICommand> &) {
	if (mListener)
		mListener->onClientListGames(*this);
}

void	Client::recvListLevels(const std::shared_ptr<ICommand> &) {
	if (mListener)
		mListener->onClientListLevels(*this);
}

void	Client::recvHandshake(const std::shared_ptr<ICommand> &command) {
	if (mListener) {
		const std::shared_ptr<CommandHandshake> commandHandshake = std::static_pointer_cast<CommandHandshake>(command);

		mListener->onClientHandshake(*this, commandHandshake->getUdpPort());
	}
}

void	Client::recvObserveGame(const std::shared_ptr<ICommand> &command) {
	if (mListener) {
		const std::shared_ptr<CommandObserveGame> commandObserveGame = std::static_pointer_cast<CommandObserveGame>(command);

		mListener->onClientObserveGame(*this, commandObserveGame->getName());
	}
}

void	Client::recvLeaveGame(const std::shared_ptr<ICommand> &) {
	if (mListener)
		mListener->onClientLeaveGame(*this);
}

void	Client::recvUpdatePseudo(const std::shared_ptr<ICommand> &command) {
	if (mListener) {
		const std::shared_ptr<CommandUpdatePseudo> commandUpdatePseudo = std::static_pointer_cast<CommandUpdatePseudo>(command);

		mListener->onClientUpdatePseudo(*this, commandUpdatePseudo->getPseudo());
	}
}

const Peer &Client::getPeer(void) const {
	return mPeer;
}

const std::string &Client::getPseudo(void) const {
	return mPseudo;
}

void Client::setPseudo(const std::string &pseudo) {
	mPseudo = pseudo;
}

bool Client::isAuthenticated(void) const {
	return mIsAuthenticated;
}

void Client::setIsAuthenticated(bool isAuthenticated) {
	mIsAuthenticated = isAuthenticated;
}

void Client::handshake(int port) {
	CommandHandshake commandHandShake;

	commandHandShake.setUdpPort(port);
	mClientPacketBuilder.sendCommand(&commandHandShake);
}

void	Client::sendError(const ErrorStatus &errorStatus) {
	CommandError commandError;

	commandError.setErrorCode(errorStatus.getErrorCode());
	mClientPacketBuilder.sendCommand(&commandError);
}

void	Client::sendShowGame(const std::string &name, const std::string &levelName, int nbPlayers, int maxPlayers, int nbObservers, int maxObservers) {
	CommandShowGame commandShowGame;

	commandShowGame.setName(name);
	commandShowGame.setLevelName(levelName);
	commandShowGame.setNbPlayers(nbPlayers);
	commandShowGame.setMaxPlayers(maxPlayers);
	commandShowGame.setNbObservers(nbObservers);
	commandShowGame.setMaxObservers(maxObservers);
	mClientPacketBuilder.sendCommand(&commandShowGame);
}

void	Client::sendEndGame(void) {
	CommandEndGame commandEndGame;

	mClientPacketBuilder.sendCommand(&commandEndGame);
}

void	Client::sendShowLevel(const std::string &name) {
	CommandShowLevel commandShowLevel;

	commandShowLevel.setName(name);
	mClientPacketBuilder.sendCommand(&commandShowLevel);
}

void Client::setUdpPort(int udpPort) {
	mPeer.udpPort = udpPort;
}

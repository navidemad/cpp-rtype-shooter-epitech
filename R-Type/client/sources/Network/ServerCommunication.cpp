#include "Network/ServerCommunication.hpp"
#include "Network/TcpClient.hpp"
#include "CommandDestroyResource.hpp"
#include "CommandEndGame.hpp"
#include "CommandError.hpp"
#include "CommandMoveResource.hpp"
#include "CommandShowGame.hpp"
#include "CommandShowLevel.hpp"
#include "CommandTimeElapsedPing.hpp"
#include "CommandUpdateScore.hpp"
#include "CommandHandshake.hpp"
#include "CommandCreateGame.hpp"
#include "CommandDeleteGame.hpp"
#include "CommandFire.hpp"
#include "CommandJoinGame.hpp"
#include "CommandLeaveGame.hpp"
#include "CommandListGames.hpp"
#include "CommandListLevels.hpp"
#include "CommandMove.hpp"
#include "CommandObserveGame.hpp"
#include "CommandShowGame.hpp"
#include "CommandUpdatePseudo.hpp"
#include "SocketException.hpp"
#include <memory>

#include <iostream>

/*
** ctor - dtor
*/
ServerCommunication::ServerCommunication(int ClientPortUdp)
: QObject(), mClientPortUdp(ClientPortUdp), mSocketTcp(new TcpClient()), mCmdTcp(mSocketTcp), mCmdUdp(mClientPortUdp){
	mCmdTcp.setListener(this);
	mCmdUdp.setListener(this);
}

ServerCommunication::~ServerCommunication() {
}

/*
**slots
*/
bool ServerCommunication::OnCreateGame(const std::string &name, const std::string &levelName, int nbPlayer, int nbObserver){
	std::shared_ptr<ICommand> command(new CommandCreateGame);
	CommandCreateGame *fill = reinterpret_cast<CommandCreateGame *>(command.get());

	fill->setName(name);
	fill->setLevelName(levelName);
	fill->setNbPlayers(nbPlayer);
	fill->setNbSpectators(nbObserver);

	return sendCommand(command.get(), true);
}

bool ServerCommunication::OnDeleteGame(const std::string &name){
	std::shared_ptr<ICommand> command(new CommandDeleteGame);
	CommandDeleteGame *fill = reinterpret_cast<CommandDeleteGame *>(command.get());

	fill->setName(name);

	return sendCommand(command.get(), true);
}

bool ServerCommunication::OnFire(void){
	std::shared_ptr<ICommand> command(new CommandFire);

	return sendCommand(command.get(), false);
}

bool ServerCommunication::OnJoinGame(const std::string &name){
	std::shared_ptr<ICommand> command(new CommandJoinGame);
	CommandJoinGame *fill = reinterpret_cast<CommandJoinGame *>(command.get());

	fill->setName(name);

	return sendCommand(command.get(), true);
}

bool ServerCommunication::OnLeaveGame(void){
	std::shared_ptr<ICommand> command(new CommandLeaveGame);

	return sendCommand(command.get(), true);
}

bool ServerCommunication::OnListGame(void){
	std::shared_ptr<ICommand> command(new CommandListGames);

	return sendCommand(command.get(), true);
}

bool ServerCommunication::OnListLevel(void){
	std::shared_ptr<ICommand> command(new CommandListLevels);

	return sendCommand(command.get(), true);
}

bool ServerCommunication::OnMove(IResource::Direction direction){
	std::shared_ptr<ICommand> command(new CommandMove);
	CommandMove *fill = reinterpret_cast<CommandMove *>(command.get());

	fill->setDirection(direction);

	return sendCommand(command.get(), false);
}

bool ServerCommunication::OnObserveGame(const std::string &name){
	std::shared_ptr<ICommand> command(new CommandObserveGame);
	CommandObserveGame *fill = reinterpret_cast<CommandObserveGame *>(command.get());

	fill->setName(name);

	return sendCommand(command.get(), true);
}

bool ServerCommunication::OnShowGame(const std::string &name){
	std::shared_ptr<ICommand> command(new CommandShowGame);
	CommandShowGame *fill = reinterpret_cast<CommandShowGame *>(command.get());

	fill->setName(name);

	return sendCommand(command.get(), true);
}

bool ServerCommunication::OnUpdatePseudo(const std::string &pseudo){
	std::shared_ptr<ICommand> command(new CommandUpdatePseudo);
	CommandUpdatePseudo *fill = reinterpret_cast<CommandUpdatePseudo *>(command.get());

	fill->setPseudo(pseudo);

	return sendCommand(command.get(), true);
}

void ServerCommunication::OnSetServerIp(const std::string &ip){
	mServerPeer.host = ip;
}

void ServerCommunication::OnSetServerPortTcp(int port){
	mServerPeer.tcpPort = port;
}

bool ServerCommunication::OnConnectToServer(void){
	try {
		mSocketTcp->connect(mServerPeer.host, mServerPeer.tcpPort);
	}
	catch (SocketException){
		return false;
	}
	return true;
}

/*
**handle command from server
*/
const ServerCommunication::HandleServerCommand ServerCommunication::tabHandleServerCommand[] = {
	{ICommand::Instruction::DESTROY_RESOURCE, &ServerCommunication::ExecDestroyResource},
	{ICommand::Instruction::END_GAME, &ServerCommunication::ExecEndGame},
	{ICommand::Instruction::ERROR, &ServerCommunication::ExecError},
	{ICommand::Instruction::MOVE_RESOURCE, &ServerCommunication::ExecMoveResource},
	{ICommand::Instruction::SHOW_GAME, &ServerCommunication::ExecShowGame},
	{ICommand::Instruction::SHOW_LEVEL, &ServerCommunication::ExecShowLevel},
	{ICommand::Instruction::TIME_ELAPSED_PING, &ServerCommunication::ExecTimeElapse},
	{ICommand::Instruction::UPDATE_SCORE, &ServerCommunication::ExecUpdateScore},
	{ICommand::Instruction::HANDSHAKE, &ServerCommunication::ExecHandShake},
	{ICommand::Instruction::UNKNOWN, NULL}};

void ServerCommunication::ExecServerCommand(ICommand *command){
	ICommand::Instruction key = command->getInstruction();
	int i = 0;

	while (tabHandleServerCommand[i].key != ICommand::Instruction::UNKNOWN) {
		if (tabHandleServerCommand[i].key == key)
			(this->*tabHandleServerCommand[i].fct)(command);
		i++;
	}
}

void ServerCommunication::ExecDestroyResource(ICommand *command) {
	CommandDestroyResource *cmd = reinterpret_cast<CommandDestroyResource *>(command);

	emit SignalDestroyResource(cmd->getId());
}

void ServerCommunication::ExecEndGame(ICommand *command){
	CommandEndGame*cmd = reinterpret_cast<CommandEndGame *>(command);

	emit SignalEndGame(cmd->getName());
}

void ServerCommunication::ExecError(ICommand *command){
	CommandError *cmd = reinterpret_cast<CommandError *>(command);

	emit SignalError(cmd->getInstructionCode(), cmd->getErrorCode());
}

void ServerCommunication::ExecMoveResource(ICommand *command){
	CommandMoveResource *cmd = reinterpret_cast<CommandMoveResource*>(command);

	emit SignalMoveResource(cmd->getType(), cmd->getX(), cmd->getY(), cmd->getAngle(), cmd->getId());
}

void ServerCommunication::ExecShowGame(ICommand *command){
	CommandShowGame *cmd = reinterpret_cast<CommandShowGame *>(command);

	emit SignalShowGame(cmd->getName(), cmd->getLevelName(), cmd->getNbPlayers(), cmd->getMaxPlayers(), cmd->getNbObservers(), cmd->getMaxObservers());
}

void ServerCommunication::ExecShowLevel(ICommand *command){
	CommandShowLevel *cmd = reinterpret_cast<CommandShowLevel *>(command);

	emit SignalShowLevel(cmd->getName(), cmd->getScript());
}

void ServerCommunication::ExecTimeElapse(ICommand *command){
	CommandTimeElapsedPing *cmd = reinterpret_cast<CommandTimeElapsedPing *>(command);

	emit SignalTimeElapse(cmd->getTimeElapsed());
}

void ServerCommunication::ExecUpdateScore(ICommand *command){
	CommandUpdateScore *cmd = reinterpret_cast<CommandUpdateScore *>(command);

	emit SignalUpdateScore(cmd->getPseudo(), cmd->getId(), cmd->getScore());
}

void ServerCommunication::ExecHandShake(ICommand * command){
	CommandHandshake *cmd = reinterpret_cast<CommandHandshake *>(command);

	mServerPeer.udpPort = cmd->getUdpPort();
	cmd->setUdpPort(mClientPortUdp);

	sendCommand(command, true);
}

/*
** Callback from ClientPacketBuilder
*/
void    ServerCommunication::onPacketAvailable(const ClientPacketBuilder &/*clientPacketBuilder*/, const std::shared_ptr<ICommand> &command){
	ExecServerCommand(command.get());
}

void    ServerCommunication::onSocketClosed(const ClientPacketBuilder &/*clientPacketBuilder*/){
	emit SignalCloseSocket();
}

/*
** Callback from PlayerPacketBuilder
*/
void ServerCommunication::onPacketAvailable(const PlayerPacketBuilder &/*clientPacketBuilder*/, const std::shared_ptr<ICommand> &command, const Peer &/*peer*/){
	ExecServerCommand(command.get());
}

/*
**dry
*/
bool ServerCommunication::sendCommand(ICommand *command, bool isTcpCommand){
	try {
		if (isTcpCommand)
			mCmdTcp.sendCommand(command);
		else
			mCmdUdp.sendCommand(command, mServerPeer);
	}
	catch (SocketException) {
		return false;
	}
	return true;
}
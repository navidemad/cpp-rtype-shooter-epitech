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
#include "CommandDisconnect.hpp"
#include "CommandFire.hpp"
#include "CommandJoinGame.hpp"
#include "CommandLeaveGame.hpp"
#include "CommandListGames.hpp"
#include "CommandListLevels.hpp"
#include "CommandMove.hpp"
#include "CommandObserveGame.hpp"
#include "CommandShowGame.hpp"
#include "CommandUpdatePseudo.hpp"
#include <memory>

#include <iostream>

/*
** ctor - dtor
*/
ServerCommunication::ServerCommunication()
: QObject(), mSocketTcp(new TcpClient()), mCmdTcp(mSocketTcp), mCmdUdp(4242){
	mCmdTcp.setListener(this);
	mCmdUdp.setListener(this);
}

ServerCommunication::~ServerCommunication() {
}

/*
**slots
*/
void ServerCommunication::OnCreateGame(const std::string &name, const std::string &levelName, int nbPlayer, int nbObserver){
	std::shared_ptr<ICommand> command(new CommandCreateGame);
	CommandCreateGame *fill = reinterpret_cast<CommandCreateGame *>(command.get());

	fill->setName(name);
	fill->setLevelName(levelName);
	fill->setNbPlayers(nbPlayer);
	fill->setNbSpectators(nbObserver);

	std::cout << "send OnCreateGame" << std::endl;
	mCmdTcp.sendCommand(command.get());
}

void ServerCommunication::OnDeleteGame(const std::string &name){
	std::shared_ptr<ICommand> command(new CommandDeleteGame);
	CommandDeleteGame *fill = reinterpret_cast<CommandDeleteGame *>(command.get());

	fill->setName(name);

	std::cout << "Send DeleteGame" << std::endl;
	mCmdTcp.sendCommand(command.get());
}

void ServerCommunication::OnDiconect(void){
	std::shared_ptr<ICommand> command(new CommandDisconnect);

	std::cout << "Send Disconect" << std::endl;
	mCmdTcp.sendCommand(command.get());
}

void ServerCommunication::OnFire(void){
	/*
	** TO REMOVE
	*/
	Peer peer;
	peer.host = "10.41.173.139";
	peer.udpPort = 4242;
	std::shared_ptr<ICommand> command(new CommandFire);

	std::cout << "Send Onfire" << std::endl;

	mCmdUdp.sendCommand(command.get(), peer);
}

void ServerCommunication::OnJoinGame(const std::string &name){
	std::shared_ptr<ICommand> command(new CommandJoinGame);
	CommandJoinGame *fill = reinterpret_cast<CommandJoinGame *>(command.get());

	fill->setName(name);
	std::cout << "Send JoinGame" << std::endl;
	mCmdTcp.sendCommand(command.get());
}

void ServerCommunication::OnLeaveGame(void){
	std::shared_ptr<ICommand> command(new CommandLeaveGame);
	std::cout << "Send LeaveGame" << std::endl;
	mCmdTcp.sendCommand(command.get());
}

void ServerCommunication::OnListGame(void){
	std::shared_ptr<ICommand> command(new CommandListGames);

	std::cout << "Send listGame" << std::endl;
	mCmdTcp.sendCommand(command.get());
}

void ServerCommunication::OnListLevel(void){
	std::shared_ptr<ICommand> command(new CommandListLevels);

	std::cout << "Send listlevel" << std::endl;

	mCmdTcp.sendCommand(command.get());
}

void ServerCommunication::OnMove(IResource::Direction direction){
	/*
	** TO REMOVE
	*/
	Peer peer;
	peer.host = "10.41.173.139";
	peer.udpPort = 4242;
	std::shared_ptr<ICommand> command(new CommandMove);
	CommandMove *fill = reinterpret_cast<CommandMove *>(command.get());

	fill->setDirection(direction);

	std::cout << "Send Move" << std::endl;
	mCmdUdp.sendCommand(command.get(), peer);
}

void ServerCommunication::OnObserveGame(const std::string &name){
	std::shared_ptr<ICommand> command(new CommandObserveGame);
	CommandObserveGame *fill = reinterpret_cast<CommandObserveGame *>(command.get());

	fill->setName(name);

	std::cout << "Send Observer game" << std::endl;
	mCmdTcp.sendCommand(command.get());
}

void ServerCommunication::OnShowGame(const std::string &name){
	std::shared_ptr<ICommand> command(new CommandShowGame);
	CommandShowGame *fill = reinterpret_cast<CommandShowGame *>(command.get());

	fill->setName(name);

	std::cout << "Send SHOW_GAME" << std::endl;
	mCmdTcp.sendCommand(command.get());
}

void ServerCommunication::OnUpdatePseudo(const std::string &pseudo){
	std::shared_ptr<ICommand> command(new CommandUpdatePseudo);
	CommandUpdatePseudo *fill = reinterpret_cast<CommandUpdatePseudo *>(command.get());

	fill->setPseudo(pseudo);

	std::cout << "Send Updatepseudo" << std::endl;
	mCmdTcp.sendCommand(command.get());
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
	std::cout << "Receive DESTROY_RESOURCE" << std::endl;
	//emit SignalDestroyResource(cmd->getId());
}

void ServerCommunication::ExecEndGame(ICommand *command){
	CommandEndGame*cmd = reinterpret_cast<CommandEndGame *>(command);
	std::cout << "Receive END_GAME" << std::endl;
	//emit SignalEndGame(cmd->getName());
}

void ServerCommunication::ExecError(ICommand *command){
	CommandError *cmd = reinterpret_cast<CommandError *>(command);

	std::cout << "Receive ERROR" << std::endl;
	if ((int)cmd->getErrorCode() == 1)
		std::cout << "Fail" << std::endl;
	//emit SignalError(cmd->getInstructionCode(), cmd->getErrorCode());
}

void ServerCommunication::ExecMoveResource(ICommand *command){
	CommandMoveResource *cmd = reinterpret_cast<CommandMoveResource*>(command);
	std::cout << "Receive MOVE_RESOURCE" << std::endl;
	//emit SignalMoveResource(cmd->getType(), cmd->getX(), cmd->getY(), cmd->getAngle(), cmd->getId());
}

void ServerCommunication::ExecShowGame(ICommand *command){
	CommandShowGame *cmd = reinterpret_cast<CommandShowGame *>(command);
	std::cout << "Receive SHOW_GAME" << std::endl;
	//emit SignalShowGame(cmd->getName(), cmd->getLevelName(), cmd->getNbPlayers(), cmd->getMaxPlayers(), cmd->getNbObservers(), cmd->getMaxObservers());
}

void ServerCommunication::ExecShowLevel(ICommand *command){
	CommandShowLevel *cmd = reinterpret_cast<CommandShowLevel *>(command);
	std::cout << "Receive SHOW_LEVEL" << std::endl;
	std::cout << cmd->getName() << std::endl;
	//emit SignalShowLevel(cmd->getName(), cmd->getScript());
}

void ServerCommunication::ExecTimeElapse(ICommand *command){
	CommandTimeElapsedPing *cmd = reinterpret_cast<CommandTimeElapsedPing *>(command);
	std::cout << "Receive TIME_ELAPSED_PING" << std::endl;
	//emit SignalTimeElapse(cmd->getTimeElapsed());
}

void ServerCommunication::ExecUpdateScore(ICommand *command){
	CommandUpdateScore *cmd = reinterpret_cast<CommandUpdateScore *>(command);
	std::cout << "Receive UPDATE_SCORE" << std::endl;
	//emit SignalUpdateScore(cmd->getPseudo(), cmd->getId(), cmd->getScore());
}

void ServerCommunication::ExecHandShake(ICommand * /*command*/){
	std::shared_ptr<ICommand> command(new CommandHandshake);
	std::cout << "Receive Handshake" << std::endl;

	std::cout << "Send Handshake" << std::endl;
	mCmdTcp.sendCommand(command.get());

    OnFire();

    OnCreateGame(std::string ("name"), std::string ("levelname"), 4, 4);
    OnJoinGame(std::string ("name"));

    OnFire();
    OnMove(IResource::Direction::RIGHT);
}

/*
** Callback from ClientPacketBuilder
*/
void    ServerCommunication::onPacketAvailable(const ClientPacketBuilder &/*clientPacketBuilder*/, const std::shared_ptr<ICommand> &command){
	ExecServerCommand(command.get());
}

void    ServerCommunication::onSocketClosed(const ClientPacketBuilder &/*clientPacketBuilder*/){
	return ;
}

/*
** Callback from PlayerPacketBuilder
*/
void ServerCommunication::onPacketAvailable(const PlayerPacketBuilder &/*clientPacketBuilder*/, const std::shared_ptr<ICommand> &command, const Peer &/*peer*/){
	ExecServerCommand(command.get());
}

/*
** Handle socket
*/
void ServerCommunication::connectSocketTcp(void){
	mSocketTcp->connect(mIpTcp, mPortTcp);
}

/*
** Getter
*/
std::list<ICommand *> &ServerCommunication::getCommand(void) {
	return mListCommand;
}

/*
** Setter
*/
void ServerCommunication::setServerTcp(int port, std::string ip){
	mPortTcp = port;
	mIpTcp = ip;
}


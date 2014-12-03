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
#include <memory>

/*
** ctor - dtor
*/
ServerCommunication::ServerCommunication()
: mSocketTcp(new TcpClient()), mCmdTcp(mSocketTcp), mCmdUdp(4242){
	mCmdTcp.setListener(this);
	mCmdUdp.setListener(this);
}

ServerCommunication::~ServerCommunication() {
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
void ServerCommunication::ExecDestroyResource(ICommand *command){
	CommandDestroyResource *cmd = reinterpret_cast<CommandDestroyResource *>(command);
	mListenerEcs->OnDestroyResource(cmd->getId());
}
void ServerCommunication::ExecEndGame(ICommand *command){
	CommandEndGame*cmd = reinterpret_cast<CommandEndGame *>(command);
	mListenerEcs->OnEndGame(cmd->getName());
}
void ServerCommunication::ExecError(ICommand *command){
	CommandError *cmd = reinterpret_cast<CommandError *>(command);
	mListenerEcs->OnError(cmd->getInstructionCode(), cmd->getErrorCode());
}
void ServerCommunication::ExecMoveResource(ICommand *command){
	CommandMoveResource *cmd = reinterpret_cast<CommandMoveResource*>(command);
	mListenerEcs->OnMoveResource(cmd->getType(), cmd->getX(), cmd->getY(), cmd->getAngle(), cmd->getId());
}
void ServerCommunication::ExecShowGame(ICommand *command){
	CommandShowGame *cmd = reinterpret_cast<CommandShowGame *>(command);
	mListenerEcs->OnShowGame(cmd->getName(), cmd->getLevelName(), cmd->getNbPlayers(), cmd->getMaxPlayers(), cmd->getNbObservers(), cmd->getMaxObservers());
}
void ServerCommunication::ExecShowLevel(ICommand *command){
	CommandShowLevel *cmd = reinterpret_cast<CommandShowLevel *>(command);
	mListenerEcs->OnShowLevel(cmd->getName(), cmd->getScript());
}
void ServerCommunication::ExecTimeElapse(ICommand *command){
	CommandTimeElapsedPing *cmd = reinterpret_cast<CommandTimeElapsedPing *>(command);
	mListenerEcs->OnTimeElapse(cmd->getTimeElapsed());
}
void ServerCommunication::ExecUpdateScore(ICommand *command){
	CommandUpdateScore *cmd = reinterpret_cast<CommandUpdateScore *>(command);
	mListenerEcs->OnUpdateScore(cmd->getPseudo(), cmd->getId(), cmd->getScore());
}
void ServerCommunication::ExecHandShake(ICommand * /*command*/){
	
}

/*
** Callback from ClientPacketBuilder
*/
void    ServerCommunication::onPacketAvailable(const ClientPacketBuilder &/*clientPacketBuilder*/, const std::shared_ptr<ICommand> &/*command*/){

}
void    ServerCommunication::onSocketClosed(const ClientPacketBuilder &/*clientPacketBuilder*/){

}

/*
** Callback from PlayerPacketBuilder
*/
void ServerCommunication::onPacketAvailable(const PlayerPacketBuilder &/*clientPacketBuilder*/, const std::shared_ptr<ICommand> &/*command*/, const Peer &/*peer*/){

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
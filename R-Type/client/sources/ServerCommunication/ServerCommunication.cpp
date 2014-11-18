#include "ServerCommunication.hpp"
#include "CommandShow.hpp"
#include "CommandAdd.hpp"
#include "CommandDel.hpp"
#include "CommandSend.hpp"
#include "CommandCall.hpp"
#include "CommandAcceptCall.hpp"
#include "CommandCloseCall.hpp"
#include "CommandReg.hpp"
#include "CommandLog.hpp"
#include "CommandList.hpp"
#include "CommandExit.hpp"
#include "CommandAcceptAdd.hpp"
#include "CommandUpdate.hpp"
#include "CommandErr.hpp"
#include "CommandHandshake.hpp"
#include "SocketException.hpp"	

const ServerCommunication::HandleCommand ServerCommunication::handleCommandsTab[] = {
	{ ICommand::SHOW,					&ServerCommunication::handleShowCommand			},
	{ ICommand::ADD,					&ServerCommunication::handleAddCommand			},
	{ ICommand::DEL,					&ServerCommunication::handleDelCommand			},
	{ ICommand::SEND,					&ServerCommunication::handleSendCommand			},
	{ ICommand::CALL,					&ServerCommunication::handleCallCommand			},
	{ ICommand::ACCEPT_CALL,			&ServerCommunication::handleAcceptCallCommand	},
	{ ICommand::CLOSE_CALL,				&ServerCommunication::handleCloseCallCommand	},
	{ ICommand::ERR,					&ServerCommunication::handleErrCommand			},
    { ICommand::HANDSHAKE,              &ServerCommunication::handleHandshakeCommand    },
	{ ICommand::UNKNOWN_INSTRUCTION,	NULL											}
};

const ServerCommunication::HandleError ServerCommunication::handleErrorsTab[] = {
	{ ICommand::REG,					&ServerCommunication::receiveServerAnswerForRegistration			},
	{ ICommand::LOG,					&ServerCommunication::receiveServerAnswerForAuthentication			},
	{ ICommand::ADD,					&ServerCommunication::receiveServerAnswerForAddingContact			},
	{ ICommand::ACCEPT_ADD,				&ServerCommunication::receiveServerAnswerForAcceptingContact		},
	{ ICommand::DEL,					&ServerCommunication::receiveServerAnswerForDeletingContact			},
	{ ICommand::EXIT,					&ServerCommunication::receiveServerAnswerForDisconnecting			},
	{ ICommand::UPDATE,					&ServerCommunication::receiveServerAnswerForUpdatingInfo			},
	{ ICommand::SEND,					&ServerCommunication::receiveServerAnswerForSendingMessage			},
	{ ICommand::CALL,					&ServerCommunication::receiveServerAnswerForCallingContact			},
	{ ICommand::ACCEPT_CALL,			&ServerCommunication::receiveServerAnswerForAcceptingCallInvitation	},
	{ ICommand::CLOSE_CALL,				&ServerCommunication::receiveServerAnswerForTerminatingCall			},
	{ ICommand::UNKNOWN_INSTRUCTION,	NULL																}
};

ServerCommunication::ServerCommunication(void) : mHasHandshaked(false) {
	connect(&mCommandPacketBuilder, SIGNAL(receiveCommand(const ICommand *)), this, SLOT(treatCommand(const ICommand *)));
	connect(&mCommandPacketBuilder, SIGNAL(disconnectedFromHost()), this, SLOT(onDisconnection()));
}

ServerCommunication::~ServerCommunication(void) {
}

void	ServerCommunication::treatCommand(const ICommand *command) {
	ICommand::Instruction instruction = command->getInstruction();

    if (mHasHandshaked == false && instruction != ICommand::HANDSHAKE) {
        mCommandPacketBuilder.close();
        return;
    }

	int i;
	for (i = 0; handleCommandsTab[i].instruction != ICommand::UNKNOWN_INSTRUCTION && handleCommandsTab[i].instruction != instruction; i++);

	if (handleCommandsTab[i].instruction == instruction)
		(this->*handleCommandsTab[i].handler)(command);
}

void    ServerCommunication::handleHandshakeCommand(const ICommand *) {
    mHasHandshaked = true;
}

void	ServerCommunication::handleShowCommand(const ICommand *command) {
	const CommandShow *commandShow = dynamic_cast<const CommandShow *>(command);

	Contact contact;
	contact.setAccountName(commandShow->getAccountName());
	contact.setPseudo(commandShow->getPseudo());
	contact.setStatus(commandShow->getStatus());
	contact.setIsConnected(commandShow->isConnected());

	emit receiveContactInfo(contact);
}

void	ServerCommunication::handleAddCommand(const ICommand *command) {
	const CommandAdd *commandAdd = dynamic_cast<const CommandAdd *>(command);

	Contact contact;
	contact.setAccountName(commandAdd->getAccountName());
	emit receiveContactInvitation(contact);
}

void	ServerCommunication::handleDelCommand(const ICommand *command) {
	const CommandDel *commandDel = dynamic_cast<const CommandDel *>(command);

	Contact contact;
	contact.setAccountName(commandDel->getAccountName());

	emit receiveContactDeletion(contact);
}

void	ServerCommunication::handleSendCommand(const ICommand *command) {
	const CommandSend *commandSend = dynamic_cast<const CommandSend *>(command);

	Contact contact;
	contact.setAccountName(commandSend->getAccountName());

	emit receiveMessage(contact, commandSend->getTextMessage());
}

void	ServerCommunication::handleCallCommand(const ICommand *command) {
	const CommandCall *commandCall = dynamic_cast<const CommandCall *>(command);

	Contact contact;
	contact.setAccountName(commandCall->getAccountName());

	emit receiveCallInvitation(contact);
}

void	ServerCommunication::handleAcceptCallCommand(const ICommand *command) {
	const CommandAcceptCall *commandAcceptCall = dynamic_cast<const CommandAcceptCall *>(command);

	Contact contact;
	contact.setAccountName(commandAcceptCall->getAccountName());
	contact.setHost(commandAcceptCall->getHost());

	emit receiveCallAnswer(contact, commandAcceptCall->hasAccepted());
}

void	ServerCommunication::handleCloseCallCommand(const ICommand *command) {
	const CommandCloseCall *commandCloseCall = dynamic_cast<const CommandCloseCall *>(command);

	Contact contact;
	contact.setAccountName(commandCloseCall->getAccountName());

	emit receiveCallClose(contact);
}

void	ServerCommunication::handleErrCommand(const ICommand *command) {
	const CommandErr *commandErr = dynamic_cast<const CommandErr *>(command);
	ICommand::Instruction instruction = commandErr->getInstructionCode();

	ErrorStatus errorStatus;
	errorStatus.setErrorCode(commandErr->getErrorCode());
	errorStatus.setErrorOccurred(commandErr->getErrorCode() != ErrorStatus::OK);

	int i;
	for (i = 0; handleErrorsTab[i].instruction != ICommand::UNKNOWN_INSTRUCTION && handleErrorsTab[i].instruction != instruction; i++);
	if (handleErrorsTab[i].instruction == instruction)
		emit (this->*handleErrorsTab[i].signal)(errorStatus);
}

void	ServerCommunication::createAccount(const Contact &contact) {
	CommandReg *commandReg = new CommandReg;

	commandReg->setAccountName(contact.getAccountName());
	commandReg->setPseudo(contact.getPseudo());
	commandReg->setPassword(contact.getPassword());

	mCommandPacketBuilder.sendCommand(commandReg);
}

void	ServerCommunication::authenticate(const Contact &contact) {
	CommandLog *commandLog = new CommandLog;

	commandLog->setAccountName(contact.getAccountName());
	commandLog->setPassword(contact.getPassword());

	mCommandPacketBuilder.sendCommand(commandLog);
}

void	ServerCommunication::getContactsInfo(void) {
	mCommandPacketBuilder.sendCommand(new CommandList);
}

void	ServerCommunication::getContactInfo(const Contact &contact) {
	CommandShow *commandShow = new CommandShow;

	commandShow->setAccountName(contact.getAccountName());

	mCommandPacketBuilder.sendCommand(commandShow);
}

void	ServerCommunication::addContact(const Contact &contact) {
	CommandAdd *commandAdd = new CommandAdd;

	commandAdd->setAccountName(contact.getAccountName());

	mCommandPacketBuilder.sendCommand(commandAdd);
}

void	ServerCommunication::acceptContactInvitation(const Contact &contact, bool hasAccepted) {
	CommandAcceptAdd *commandAcceptAdd = new CommandAcceptAdd;

	commandAcceptAdd->setAccountName(contact.getAccountName());
	commandAcceptAdd->setHasAccepted(hasAccepted);

	mCommandPacketBuilder.sendCommand(commandAcceptAdd);
}

void	ServerCommunication::deleteContact(const Contact &contact) {
	CommandDel *commandDel = new CommandDel;

	commandDel->setAccountName(contact.getAccountName());

	mCommandPacketBuilder.sendCommand(commandDel);
}

void	ServerCommunication::sendMessage(const Contact &contact, const QString &message) {
	CommandSend *commandSend = new CommandSend;

	commandSend->setAccountName(contact.getAccountName());
	commandSend->setTextMessage(message);

	mCommandPacketBuilder.sendCommand(commandSend);
}

void	ServerCommunication::disconnect(void) {
	mCommandPacketBuilder.sendCommand(new CommandExit);
}

void	ServerCommunication::updateInfo(const Contact &contact) {
	CommandUpdate *commandUpdate = new CommandUpdate;

	commandUpdate->setAccountName(contact.getAccountName());
	commandUpdate->setPseudo(contact.getPseudo());
	commandUpdate->setPassword(contact.getPassword());
	commandUpdate->setStatus(contact.getStatus());

	mCommandPacketBuilder.sendCommand(commandUpdate);
}

void	ServerCommunication::call(const Contact &contact) {
	CommandCall *commandCall = new CommandCall;

	commandCall->setAccountName(contact.getAccountName());

	mCommandPacketBuilder.sendCommand(commandCall);
}

void	ServerCommunication::acceptCallInvitation(const Contact &contact, bool hasAccepted) {
	CommandAcceptCall *commandAcceptCall = new CommandAcceptCall;

	commandAcceptCall->setAccountName(contact.getAccountName());
	commandAcceptCall->setHasAccepted(hasAccepted);

	mCommandPacketBuilder.sendCommand(commandAcceptCall);
}

void	ServerCommunication::terminateCall(const Contact &contact) {
    CommandCloseCall *commandCloseCall = new CommandCloseCall;

    commandCloseCall->setAccountName(contact.getAccountName());

    mCommandPacketBuilder.sendCommand(commandCloseCall);
}

void	ServerCommunication::sendHandshake(void) {
    CommandHandshake *commandHandshake = new CommandHandshake;
   
    mCommandPacketBuilder.sendCommand(commandHandshake);
}

void	ServerCommunication::connectToServer(const QString &addr, int port) {
	ErrorStatus errorStatus;

	try {
		mCommandPacketBuilder.connectToServer(addr, port);
        sendHandshake();
		errorStatus.setErrorCode(ErrorStatus::OK);
		errorStatus.setErrorOccurred(false);
	}
	catch (const SocketException &) {
		errorStatus.setErrorCode(ErrorStatus::FAIL_INIT_SOCKET);
		errorStatus.setErrorOccurred(true);
	}

	emit receiveAnswerForConnectionToServer(errorStatus);
}

void	ServerCommunication::onDisconnection(void) {
    mHasHandshaked = false;
	emit disconnectedFromServer();
}
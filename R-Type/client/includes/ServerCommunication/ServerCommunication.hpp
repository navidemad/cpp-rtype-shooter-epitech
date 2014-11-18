#pragma once

#include <qobject.h>
#include "ICommand.hpp"
#include "CommandPacketBuilder.hpp"
#include "ErrorStatus.hpp"
#include "Contact.hpp"

class ServerCommunication : public QObject {

	Q_OBJECT

	// handle commands
	private:
		struct HandleCommand {
			ICommand::Instruction	instruction;
			void					(ServerCommunication::*handler)(const ICommand *command);
		};

		static const ServerCommunication::HandleCommand	handleCommandsTab[];

		void	handleShowCommand(const ICommand *command);
		void	handleAddCommand(const ICommand *command);
		void	handleDelCommand(const ICommand *command);
		void	handleSendCommand(const ICommand *command);
		void	handleCallCommand(const ICommand *command);
		void	handleAcceptCallCommand(const ICommand *command);
		void	handleCloseCallCommand(const ICommand *command);
		void	handleErrCommand(const ICommand *command);
        void    handleHandshakeCommand(const ICommand *command);

	// handle server errors
	private:
		struct HandleError {
			ICommand::Instruction	instruction;
			void					(ServerCommunication::*signal)(const ErrorStatus &errorStatus);
		};

		static const ServerCommunication::HandleError handleErrorsTab[];

	// signals
	signals:
		void	receiveContactInfo(const Contact &contact);
		void	receiveContactInvitation(const Contact &contact);
		void	receiveContactDeletion(const Contact &contact);
		void	receiveMessage(const Contact &contact, const QString &message);
		void	receiveCallInvitation(const Contact &contact);
		void	receiveCallAnswer(const Contact &contact, bool hasAccepted);
		void	receiveCallClose(const Contact &contact);
		void	receiveServerAnswerForRegistration(const ErrorStatus &errorStatus);
		void	receiveServerAnswerForAuthentication(const ErrorStatus &errorStatus);
		void	receiveServerAnswerForAddingContact(const ErrorStatus &errorStatus);
		void	receiveServerAnswerForAcceptingContact(const ErrorStatus &errorStatus);
		void	receiveServerAnswerForDeletingContact(const ErrorStatus &errorStatus);
		void	receiveServerAnswerForDisconnecting(const ErrorStatus &errorStatus);
		void	receiveServerAnswerForUpdatingInfo(const ErrorStatus &errorStatus);
		void	receiveServerAnswerForSendingMessage(const ErrorStatus &errorStatus);
		void	receiveServerAnswerForCallingContact(const ErrorStatus &errorStatus);
		void	receiveServerAnswerForAcceptingCallInvitation(const ErrorStatus &errorStatus);
		void	receiveServerAnswerForTerminatingCall(const ErrorStatus &errorStatus);
		void	receiveAnswerForConnectionToServer(const ErrorStatus &errorStatus);
		void	disconnectedFromServer(void);

	// send commands slots
	public slots:
		void	createAccount(const Contact &contact);
		void	authenticate(const Contact &contact);
		void	getContactsInfo(void);
		void	getContactInfo(const Contact &contact);
		void	addContact(const Contact &contact);
		void	acceptContactInvitation(const Contact &contact, bool hasAccepted);
		void	deleteContact(const Contact &contact);
		void	sendMessage(const Contact &contact, const QString &message);
		void	disconnect(void);
		void	updateInfo(const Contact &contact);
		void	call(const Contact &contact);
		void	acceptCallInvitation(const Contact &contact, bool hasAccepted);
		void	terminateCall(const Contact &contact);
		void	connectToServer(const QString &addr, int port);
		void	onDisconnection(void);
        void	sendHandshake(void);

	// ctor - dtor
	public:
		ServerCommunication(void);
		~ServerCommunication(void);

	// coplien form
	private:
		ServerCommunication(const ServerCommunication &) : QObject() {}
		const ServerCommunication &operator=(const ServerCommunication &) { return *this; }

	// receive command
	private slots :
		void	treatCommand(const ICommand *command);

	// attributes
	private:
        bool                    mHasHandshaked;
		CommandPacketBuilder	mCommandPacketBuilder;

};

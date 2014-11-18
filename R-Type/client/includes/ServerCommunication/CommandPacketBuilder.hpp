#pragma once

#include "ICommand.hpp"
#include "IClientSocket.hpp"
#include <qlist.h>
#include <qobject.h>

class CommandPacketBuilder : public QObject, public IClientSocket::OnSocketEvent {

	Q_OBJECT

	// handle build state
	private:
		enum State {
			HEADER,
			CONTENT
		};

	// ctor - dtor
	public:
		CommandPacketBuilder(void);
		~CommandPacketBuilder(void);

	// coplien form
	private:
		CommandPacketBuilder(const CommandPacketBuilder &) : QObject() {}
		const CommandPacketBuilder &operator=(const CommandPacketBuilder &) { return *this; }

	// send command
	public:
		void	connectToServer(const QString &addr, int port);
		void	sendCommand(const ICommand *command);
        void    close(void);

	// signals
	signals:
		void	receiveCommand(const ICommand *command);
		void	disconnectedFromHost(void);

	// build commands
	private:
		void	fetchCommandHeader(void);
		void	fetchCommandContent(void);

	// intern functions
	private:
		void	resetCurrentCommand(void);

	// socket events
	public:
		void	onBytesWritten(IClientSocket *, unsigned int) {}
		void	onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
		void	onSocketClosed(IClientSocket *socket);

	// attributes
	private:
		IClientSocket				*mClient;
		ICommand					*mCurrentCommand;
		CommandPacketBuilder::State	mCurrentState;

};

#pragma once
#include "ICommand.hpp"
#include "IClientSocket.hpp"

class CommandPacketBuilder : public IClientSocket::OnSocketEvent
{
	//callback for listener
	public:
		class OnCommandEvent{
			public:
				virtual			~OnCommandEvent(void) {}
				virtual	void	onNewCommand(ICommand *command) = 0;
		};

	// ctor - dtor
	public:
		CommandPacketBuilder(CommandPacketBuilder::OnCommandEvent *listener);
		~CommandPacketBuilder();

	// coplien form
	private:
		CommandPacketBuilder(CommandPacketBuilder const &) {}
		CommandPacketBuilder const	&operator=(CommandPacketBuilder const &) { return *this; }

	//callback from ISocketClient
    public:
        void    onBytesWritten(IClientSocket *socket, unsigned int nbBytes);
        void    onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead);
        void    onSocketClosed(IClientSocket *socket);

	// handle command
    public:
		void packCommand(IClientSocket *socket, ICommand *command);
	private:
		ICommand *unPackCommand(IClientSocket *socket);

	//attribut
	private:
		CommandPacketBuilder::OnCommandEvent *mListener;
};
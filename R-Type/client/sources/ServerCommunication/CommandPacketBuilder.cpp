#include "CommandPacketBuilder.hpp"
#include "TcpClient.hpp"
#include "CommandException.hpp"
#include "SocketException.hpp"

CommandPacketBuilder::CommandPacketBuilder(void)
	: mClient(NULL), mCurrentCommand(NULL), mCurrentState(CommandPacketBuilder::HEADER)
{
	mClient = new TcpClient;
	mClient->setOnSocketEventListener(this);
}

CommandPacketBuilder::~CommandPacketBuilder(void) {
	if (mClient)
		delete mClient;

    if (mCurrentCommand)
		delete mCurrentCommand;
}

void    CommandPacketBuilder::close(void) {
    mClient->closeClient();
}

void	CommandPacketBuilder::sendCommand(const ICommand *command) {
	try {
		mClient->send(command->getMessage());
	}
	catch (const SocketException &) {
		emit disconnectedFromHost();
	}
}

void	CommandPacketBuilder::connectToServer(const QString &addr, int port) {
	mClient->connect(addr.toStdString(), port);
}

void	CommandPacketBuilder::fetchCommandHeader(void) {
	IClientSocket::Message message = mClient->receive(ICommand::HEADER_SIZE);
	ICommand::Header *header = reinterpret_cast<ICommand::Header *>(message.msg);

	mCurrentCommand = ICommand::getCommand(static_cast<ICommand::Instruction>(header->instructionCode));
	mCurrentState = CommandPacketBuilder::CONTENT;

	if (header->magicCode != ICommand::MAGIC_CODE || mCurrentCommand == NULL) {
		mClient->closeClient();
		return;
	}

	onSocketReadable(mClient, mClient->nbBytesToRead());
}

void	CommandPacketBuilder::fetchCommandContent(void) {
	IClientSocket::Message message = mClient->receive(mCurrentCommand->getSizeToRead());

	try {
		mCurrentCommand->initFromMessage(message);
	}
	catch (const CommandException &) {
		mClient->closeClient();
		return;
	}

	emit receiveCommand(mCurrentCommand);

	resetCurrentCommand();
	onSocketReadable(mClient, mClient->nbBytesToRead());
}

void	CommandPacketBuilder::onSocketReadable(IClientSocket *, unsigned int nbBytesToRead) {
	if (mCurrentState == CommandPacketBuilder::HEADER && nbBytesToRead >= ICommand::HEADER_SIZE)
		fetchCommandHeader();
	else if (mCurrentState == CommandPacketBuilder::CONTENT && nbBytesToRead >= mCurrentCommand->getSizeToRead())
		fetchCommandContent();
}

void	CommandPacketBuilder::onSocketClosed(IClientSocket *) {
	resetCurrentCommand();
	emit disconnectedFromHost();
}

void	CommandPacketBuilder::resetCurrentCommand(void) {
	if (mCurrentCommand)
		delete mCurrentCommand;

	mCurrentCommand = NULL;
	mCurrentState = CommandPacketBuilder::HEADER;
}
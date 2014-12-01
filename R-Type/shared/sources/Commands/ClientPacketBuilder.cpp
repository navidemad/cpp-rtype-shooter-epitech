#include "ClientPacketBuilder.hpp"
#include "CommandFactory.hpp"
#include "CommandException.hpp"
#include <iostream>

ClientPacketBuilder::ClientPacketBuilder(const std::shared_ptr<IClientSocket> &client)
	: mState(ClientPacketBuilder::State::HEADER), mCurrentCommand(nullptr), mListener(nullptr), mClient(client)
{
	mClient->setOnSocketEventListener(this);
}

ClientPacketBuilder::~ClientPacketBuilder(void) {
	mClient->closeClient();
}

void	ClientPacketBuilder::onBytesWritten(IClientSocket *, unsigned int) {
}

void	ClientPacketBuilder::fetchHeader(void) {
	if (mClient->nbBytesToRead() < ICommand::HEADER_SIZE)
		return;

	IClientSocket::Message message = mClient->receive(ICommand::HEADER_SIZE);
	ICommand::Header header = *reinterpret_cast<ICommand::Header *>(message.msg.data());
	mCurrentCommand = CommandFactory::getCommand(static_cast<ICommand::Instruction>(header.instructionCode));

	if (header.magicCode != ICommand::MAGIC_CODE || mCurrentCommand.get() == nullptr) {
		mClient->closeClient();
		if (mListener)
			mListener->onSocketClosed(*this);
		return;
	}

	mState = ClientPacketBuilder::State::BODY;
	fetchBody();
}

void	ClientPacketBuilder::fetchBody(void) {
	if (mClient->nbBytesToRead() < mCurrentCommand->getSizeToRead())
		return;

	IClientSocket::Message message = mClient->receive(mCurrentCommand->getSizeToRead());

	try {
		mCurrentCommand->initFromMessage(message);
	}
	catch (const CommandException &e) {
		std::cerr << "CommandException error caught: " << e.what() << std::endl;
		mClient->closeClient();
		if (mListener)
			mListener->onSocketClosed(*this);
		return;
	}

	if (mListener)
		mListener->onPacketAvailable(*this, mCurrentCommand);

	mState = ClientPacketBuilder::State::HEADER;
	fetchHeader();
}

void	ClientPacketBuilder::onSocketReadable(IClientSocket *, unsigned int) {
	if (mState == ClientPacketBuilder::State::HEADER)
		fetchHeader();
	else if (mState == ClientPacketBuilder::State::BODY)
		fetchBody();
}

void	ClientPacketBuilder::onSocketClosed(IClientSocket *) {
	if (mListener)
		mListener->onSocketClosed(*this);
}

void	ClientPacketBuilder::setListener(ClientPacketBuilder::OnClientPacketBuilderEvent *listener) {
	mListener = listener;
}

void	ClientPacketBuilder::sendCommand(const ICommand *command) {
	ICommand::Header header;
	header.instructionCode = static_cast<int>(command->getInstruction());
	header.magicCode = ICommand::MAGIC_CODE;

	IClientSocket::Message message;
	IClientSocket::Message bodyMessage = command->getMessage();
	message.msg.assign(reinterpret_cast<char *>(&header), reinterpret_cast<char *>(&header + 1));
	message.msg.insert(message.msg.end(), bodyMessage.msg.begin(), bodyMessage.msg.end());
	message.msgSize = sizeof(ICommand::Header) + bodyMessage.msgSize;

	mClient->send(message);
}

const std::shared_ptr<ICommand> &ClientPacketBuilder::getCommand(void) const {
	return mCurrentCommand;
}

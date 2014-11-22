#include "ClientPacketBuilder.hpp"
#include "CommandFactory.hpp"
#include "CommandException.hpp"
#include <iostream>

ClientPacketBuilder::ClientPacketBuilder(const std::shared_ptr<IClientSocket> &client)
	: mState(ClientPacketBuilder::State::HEADER), mCurrentCommand(nullptr), mClient(client)
{
	mClient->setOnSocketEventListener(this);
}

ClientPacketBuilder::~ClientPacketBuilder(void) {
	if (mClient.get())
		mClient->closeClient();
}

void	ClientPacketBuilder::onBytesWritten(IClientSocket *, unsigned int) {
}

void	ClientPacketBuilder::fetchHeader(void) {
	if (mClient.get() == nullptr)
		return;

	if (mClient->nbBytesToRead() < ICommand::HEADER_SIZE)
		return;

	IClientSocket::Message message = mClient->receive(ICommand::HEADER_SIZE);
	ICommand::Header header = *reinterpret_cast<ICommand::Header *>(message.msg.data());
	mCurrentCommand = CommandFactory::getCommand(static_cast<ICommand::Instruction>(header.instructionCode));

	if (header.magicCode != ICommand::MAGIC_CODE || mCurrentCommand.get() == nullptr) {
		mClient->closeClient();
		mObserver.notifyObservers(ClientPacketBuilder::Event::DISCONNECTED);
		return;
	}

	mState = ClientPacketBuilder::State::BODY;
	fetchBody();
}

void	ClientPacketBuilder::fetchBody(void) {
	if (mClient.get() == nullptr)
		return;

	if (mClient->nbBytesToRead() < mCurrentCommand->getSizeToRead())
		return;

	IClientSocket::Message message = mClient->receive(mCurrentCommand->getSizeToRead());

	try {
		mCurrentCommand->initFromMessage(message);
	}
	catch (const CommandException &e) {
		std::cerr << "CommandException error caught: " << e.what() << std::endl;
		mClient->closeClient();
		mObserver.notifyObservers(ClientPacketBuilder::Event::DISCONNECTED);
		return;
	}

	mObserver.notifyObservers(ClientPacketBuilder::Event::PACKET_AVAILABLE);

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
	mObserver.notifyObservers(ClientPacketBuilder::Event::DISCONNECTED);
}

void	ClientPacketBuilder::registerObserver(ClientPacketBuilder::Event e, const std::function<void()> &fct) {
	mObserver.registerObserver(e, fct);
}

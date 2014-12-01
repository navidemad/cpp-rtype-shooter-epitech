#include "PlayerPacketBuilder.hpp"
#include "ICommand.hpp"
#include "CommandFactory.hpp"
#include "CommandException.hpp"

PlayerPacketBuilder::~PlayerPacketBuilder(void) {
}

void	PlayerPacketBuilder::cleanDatagramsList(unsigned int sizeToRead) {
	while (mDatagrams.size() > 1 && mDatagrams.front().msgSize < sizeToRead)
		mDatagrams.pop_front();
}

IClientSocket::Message	PlayerPacketBuilder::getPartOfFirstDatagram(unsigned int sizeToRead) {
	IClientSocket::Message message;

	message.msgSize = 0;
	message.host = "";
	message.port = 0;

	if (mDatagrams.size() == 0)
		return message;

	if (mDatagrams.front().msgSize <= sizeToRead) {
		message = mDatagrams.front();
		mDatagrams.pop_front();
	}
	else {
		IClientSocket::Message &datagram = mDatagrams.front();

		message.msg.insert(message.msg.end(), datagram.msg.begin(), datagram.msg.begin() + sizeToRead);
		message.msgSize = sizeToRead;
		message.host = datagram.host;
		message.port = datagram.port;

		datagram.msg.erase(datagram.msg.begin(), datagram.msg.begin() + sizeToRead);
		datagram.msgSize -= sizeToRead;
	}

	return message;
}

void	PlayerPacketBuilder::fetchHeader(void) {
	cleanDatagramsList(ICommand::HEADER_SIZE);

	if (mDatagrams.size() == 0 || mDatagrams.front().msgSize < ICommand::HEADER_SIZE)
		return;

	IClientSocket::Message message = getPartOfFirstDatagram(ICommand::HEADER_SIZE);
	ICommand::Header header = *reinterpret_cast<ICommand::Header *>(message.msg.data());
	mCurrentCommand = CommandFactory::getCommand(static_cast<ICommand::Instruction>(header.instructionCode));
	mCurrentHost = message.host;
	mCurrentPort = message.port;

	if (header.magicCode != ICommand::MAGIC_CODE || mCurrentCommand.get() == nullptr)
		return;

	mCurrentState = PlayerPacketBuilder::State::BODY;
	fetchBody();
}

void	PlayerPacketBuilder::fetchBody(void) {
	cleanDatagramsList(ICommand::HEADER_SIZE);

	if (mDatagrams.size() == 0 || mDatagrams.front().msgSize < ICommand::HEADER_SIZE)
		return;

	bool error = false;

	try {
		IClientSocket::Message message = getPartOfFirstDatagram(mCurrentCommand->getSizeToRead());

		if (message.host == mCurrentHost && message.port == mCurrentPort)
			mCurrentCommand->initFromMessage(message);
		else
			error = true;
	}
	catch (const CommandException &) {
		error = true;
	}

	if (error == false && mListener)
		mListener->onPacketAvailable(*this, mCurrentCommand, Peer{mCurrentHost, mCurrentPort});

	mCurrentState = PlayerPacketBuilder::State::HEADER;
	fetchHeader();
}

void	PlayerPacketBuilder::onSocketReadable(IClientSocket *, unsigned int) {
	fetchPackets();

	if (mCurrentState == PlayerPacketBuilder::State::HEADER)
		fetchHeader();
	else if (mCurrentState == PlayerPacketBuilder::State::BODY)
		fetchBody();
}

void	PlayerPacketBuilder::onBytesWritten(IClientSocket *, unsigned int) {
}

void	PlayerPacketBuilder::onSocketClosed(IClientSocket *) {
}

void	PlayerPacketBuilder::setListener(PlayerPacketBuilder::OnPlayerPacketBuilderEvent *listener) {
	mListener = listener;
}

void	PlayerPacketBuilder::fetchPackets(void) {
	while (mClient->nbBytesToRead() > 0) {
		IClientSocket::Message message = mClient->receive(mClient->nbBytesToRead());

		if (mDatagrams.size() > 0 && mDatagrams.back().host == message.host && mDatagrams.back().port == message.port)
			mergeWithLastDatagram(message);
		else
			mDatagrams.push_back(message);
	}
}

void	PlayerPacketBuilder::mergeWithLastDatagram(const IClientSocket::Message &message) {
	mDatagrams.back().msg.insert(mDatagrams.back().msg.end(), message.msg.begin(), message.msg.end());
	mDatagrams.back().msgSize += message.msgSize;
}

void	PlayerPacketBuilder::sendCommand(const ICommand *command, const Peer &peer) {
	ICommand::Header header;
	header.instructionCode = static_cast<int>(command->getInstruction());
	header.magicCode = ICommand::MAGIC_CODE;

	IClientSocket::Message message;
	IClientSocket::Message bodyMessage = command->getMessage();
	message.msg.assign(reinterpret_cast<char *>(&header), reinterpret_cast<char *>(&header + 1));
	message.msg.insert(message.msg.end(), bodyMessage.msg.begin(), bodyMessage.msg.end());
	message.msgSize = sizeof(ICommand::Header) + bodyMessage.msgSize;
	message.host = peer.host;
	message.port = peer.port;

	mClient->send(message);
}

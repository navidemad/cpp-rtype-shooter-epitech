#include <qhostaddress.h>
#include "Network/TcpClient.hpp"

TcpClient::TcpClient(void)
  : mQTcpSocket(new QTcpSocket(this)), mAddr(""), mPort(0), mListener(NULL) {
}

TcpClient::~TcpClient(void) {
}

void	TcpClient::connect(const std::string &addr, int port) {
	close(false);
	mQTcpSocket->connectToHost(QString(addr.c_str()), port);

	if (mQTcpSocket->waitForConnected(-1) == false)
		throw std::string("fail QTcpSocket::connectToHost & QTcpSocket::waitForConnected");

	QObject::connect(mQTcpSocket.get(), SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQTcpSocket.get(), SIGNAL(disconnected()), this, SLOT(close()));
	QObject::connect(mQTcpSocket.get(), SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

	mAddr = addr;
	mPort = port;
}

void	TcpClient::initFromSocket(void *socket, const std::string &addr, int port) {
	mQTcpSocket = std::shared_ptr<QTcpSocket>(reinterpret_cast<QTcpSocket *>(socket));

	QObject::connect(mQTcpSocket.get(), SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQTcpSocket.get(), SIGNAL(disconnected()), this, SLOT(close()));
	QObject::connect(mQTcpSocket.get(), SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

	mAddr = addr;
	mPort = port;
}

void	TcpClient::closeClient(void) {
	close();
}

void	TcpClient::close(bool callListener) {
	if (mQTcpSocket->state() == QAbstractSocket::ConnectedState)
		mQTcpSocket->disconnectFromHost();

	if (mListener && callListener)
		mListener->onSocketClosed(this);
}

void	TcpClient::send(const IClientSocket::Message &message) {
	std::string msg_str(message.msg.begin(), message.msg.end());

	int ret = mQTcpSocket->write(msg_str.c_str(), message.msgSize);

	if (ret == -1)
		throw std::string("fail QTcpSocket::write");
}

IClientSocket::Message	TcpClient::receive(unsigned int sizeToRead) {
	IClientSocket::Message message;
	std::shared_ptr<char> buffer(new char[sizeToRead]);
	int ret;


	if (nbBytesToRead() == 0) {
		message.msgSize = 0;

		return message;
	}

	ret = mQTcpSocket->read(buffer.get(), sizeToRead);
	if (ret == -1)
		throw std::string("fail QTcpSocket::read");

	message.msgSize = ret;
	message.msg.insert(message.msg.end(), buffer.get(), buffer.get() + message.msgSize);
	message.host = mAddr;
	message.port = mPort;

	return message;
}

unsigned int	TcpClient::nbBytesToRead(void) const {
	return mQTcpSocket->bytesAvailable();
}

void	TcpClient::markAsReadable(void) {
	if (mListener)
		mListener->onSocketReadable(this, mQTcpSocket->bytesAvailable());
}

void	TcpClient::bytesWritten(qint64 nbBytes) {
	if (mListener)
		mListener->onBytesWritten(this, nbBytes);
}

void	TcpClient::setOnSocketEventListener(OnSocketEvent *listener) {
	mListener = listener;
}

const std::string &TcpClient::getAddr(void) const {
	return mAddr;
}

int					TcpClient::getPort(void) const
{
	return mPort;
}

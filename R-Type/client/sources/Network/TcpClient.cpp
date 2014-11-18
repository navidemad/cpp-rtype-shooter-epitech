#include "TcpClient.hpp"
#include "SocketException.hpp"
#include <qhostaddress.h>

TcpClient::TcpClient(void)
: mQTcpSocket(NULL), mListener(NULL)
{
	mQTcpSocket = new QTcpSocket(this);
}

TcpClient::~TcpClient(void) {
	if (mQTcpSocket)
		delete mQTcpSocket;
}

void	TcpClient::connect(const std::string &addr, int port) {
	close(false);
	mQTcpSocket->connectToHost(QString(addr.c_str()), port);

	if (mQTcpSocket->waitForConnected(-1) == false)
		throw SocketException("fail QTcpSocket::connectToHost & QTcpSocket::waitForConnected");

	QObject::connect(mQTcpSocket, SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQTcpSocket, SIGNAL(disconnected()), this, SLOT(close()));
	QObject::connect(mQTcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void	TcpClient::initFromSocket(void *socket) {
	mQTcpSocket = reinterpret_cast<QTcpSocket *>(socket);

	QObject::connect(mQTcpSocket, SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQTcpSocket, SIGNAL(disconnected()), this, SLOT(close()));
	QObject::connect(mQTcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
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
	int ret = mQTcpSocket->write(message.msg, message.msgSize);

	if (ret == -1)
		throw SocketException("fail QTcpSocket::write");
}

IClientSocket::Message	TcpClient::receive(unsigned int sizeToRead) {
	IClientSocket::Message message;

	if (nbBytesToRead() == 0) {
		message.msg = "";
		message.msgSize = 0;

		return message;
	}

	message.msg = new char[sizeToRead];
	message.msgSize = mQTcpSocket->read(message.msg, sizeToRead);
    message.host = (mQTcpSocket->peerAddress()).toString().toStdString();
	message.port = mQTcpSocket->peerPort();

	if (message.msgSize == -1)
		throw SocketException("fail QTcpSocket::read");

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

std::string TcpClient::getRemoteIp() const {
    return mQTcpSocket->peerAddress().toString().toStdString();
}

#include "Network/UdpClient.hpp"
#include "SocketException.hpp"

UdpClient::UdpClient(void)
: mQUdpSocket(new QUdpSocket(this)), mIsReadable(false), mListener(NULL) {
}

UdpClient::~UdpClient(void){

}
#include <iostream>
void	UdpClient::connect(const std::string &/*addr*/, int port) {
	close();
	if (mQUdpSocket->bind(QHostAddress::Any, port) == false)
		throw SocketException("fail QUdpSocket::bind");

    std::cout << "UdpClient listen on port '" << port << "'" << std::endl;

	QObject::connect(mQUdpSocket.get(), SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQUdpSocket.get(), SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void	UdpClient::initFromSocket(void *socket, const std::string & /*addr*/, int /*port*/) {
	mQUdpSocket = std::shared_ptr<QUdpSocket>(reinterpret_cast<QUdpSocket *>(socket));

	QObject::connect(mQUdpSocket.get(), SIGNAL(readyRead()), this, SLOT(markAsReadable()));
	QObject::connect(mQUdpSocket.get(), SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void	UdpClient::closeClient(void) {
	close();
}

void	UdpClient::close(void) {
	if (mQUdpSocket->state() == QAbstractSocket::ConnectedState)
		mQUdpSocket->close();

	if (mListener)
		mListener->onSocketClosed(this);
}

void	UdpClient::send(const IClientSocket::Message &message) {
	std::string msg_str(message.msg.begin(), message.msg.end());

	mQUdpSocket->writeDatagram(msg_str.c_str(), message.msgSize, QHostAddress(QString(message.host.c_str())), message.port);
}

IClientSocket::Message	UdpClient::receive(unsigned int sizeToRead) {
	IClientSocket::Message message;
	QHostAddress host;
	quint16 port;
	std::shared_ptr<char> buffer(new char[sizeToRead]);
	int ret;

	if (nbBytesToRead() == 0) {
		message.msgSize = 0;

		return message;
	}

	ret = mQUdpSocket->readDatagram(buffer.get(), sizeToRead, &host, &port);
	if (ret == -1)
		throw SocketException("fail QUdpSocket::read");

	message.msgSize = ret;
	message.msg.insert(message.msg.end(), buffer.get(), buffer.get() + message.msgSize);
	message.host = host.toString().toStdString();
	message.port = port;
	mIsReadable = false;

	return message;
}

unsigned int	UdpClient::nbBytesToRead(void) const {
	return mQUdpSocket->bytesAvailable();
}

void	UdpClient::markAsReadable(void) {
	mIsReadable = true;

	if (mListener)
		mListener->onSocketReadable(this, mQUdpSocket->bytesAvailable());
}

void	UdpClient::bytesWritten(qint64 nbBytes) {
	if (mListener)
		mListener->onBytesWritten(this, nbBytes);
}

void	UdpClient::setOnSocketEventListener(OnSocketEvent *listener) {
	mListener = listener;
}

std::string UdpClient::getRemoteIp() const {
    return "127.0.0.1";
}

const std::string 	&UdpClient::getAddr(void) const {
	return mAddr;
}
int 				UdpClient::getPort(void) const {
	return mPort;
}
#pragma once

#include "IClientSocket.hpp"
#include <QtNetwork/qtcpsocket.h>

class TcpClient : public QObject, public IClientSocket {

	Q_OBJECT

	// default ctor-dtor
	public:
		TcpClient(void);
		~TcpClient(void);

	// private coplien form
	private:
		TcpClient(const TcpClient &) : QObject() {}
		const TcpClient &operator=(const TcpClient &) { return *this; }

	// start
	public:
		void	connect(const std::string &addr, int port);
		void	initFromSocket(void *socket);

	// close
	public slots:
		void	closeClient(void);

	// set listener
	public:
		void	setOnSocketEventListener(IClientSocket::OnSocketEvent *listener);

	// recv / send
	public:
		void			send(const Message &message);
		Message			receive(unsigned int sizeToRead);
		unsigned int	nbBytesToRead(void) const;

    // get host ip
    public:
        std::string getRemoteIp() const;

    // slots
	private slots:
		void	bytesWritten(qint64 nbBytes);
		void	markAsReadable(void);
		void	close(bool callListener = true);

	// attributes
	private:
		QTcpSocket	*mQTcpSocket;

		IClientSocket::OnSocketEvent	*mListener;

};

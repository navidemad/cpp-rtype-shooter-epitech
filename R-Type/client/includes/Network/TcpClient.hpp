#pragma once

#include "IClientSocket.hpp"
#include "NoCopyable.hpp"
#include <QtNetwork/qtcpsocket.h>
#include <memory>


class TcpClient : public QObject, public NoCopyable, public IClientSocket{

	Q_OBJECT

    // ctor - dtor
    public:
        TcpClient();
        ~TcpClient();

	// start
	public:
		void	connect(const std::string &addr, int port);
		void	initFromSocket(void *socket, const std::string &addr, int port);

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
        const std::string	&getAddr(void) const;
		int					getPort(void) const;

    // slots
	private slots:
		void	bytesWritten(qint64 nbBytes);
		void	markAsReadable(void);
		void	close(bool callListener = true);

	// attributes
	private:
		std::shared_ptr<QTcpSocket>		mQTcpSocket;
		std::string						mAddr;
		int				mPort;
		IClientSocket::OnSocketEvent	*mListener;
};

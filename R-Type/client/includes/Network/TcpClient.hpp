#pragma once

#include "IClientSocket.hpp"
#include <QtNetwork/qtcpsocket.h>
#include <memory>


class TcpClient : public QObject, public IClientSocket{

	Q_OBJECT

    // ctor - dtor
    public:
        explicit TcpClient();
        ~TcpClient();

    // copy operators
    public:
        TcpClient(const TcpClient &) = delete;
        TcpClient(TcpClient &&) = delete;
        const TcpClient &operator=(const TcpClient &) = delete;
        const TcpClient &operator=(TcpClient &&) = delete;

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
		std::shared_ptr<QTcpSocket>	mQTcpSocket;

		IClientSocket::OnSocketEvent	*mListener;
};

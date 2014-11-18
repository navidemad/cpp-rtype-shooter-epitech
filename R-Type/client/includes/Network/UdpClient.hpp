#pragma once

#include "IClientSocket.hpp"
#include <QtNetwork/qudpsocket.h>

class UdpClient : public QObject, public IClientSocket {

	Q_OBJECT

	// default ctor-dtor
	public:
		UdpClient(void);
		~UdpClient(void);

	// private coplien form
	private:
		UdpClient(const UdpClient &) : QObject() {}
		const UdpClient &operator=(const UdpClient &) { return *this; }

	// start-stop
	public:
		void	connect(const std::string &addr, int port);
		void	initFromSocket(void *socket);
		void	closeClient(void);

    // get host ip
    public:
        std::string getRemoteIp() const;
    
    // set listener
	public:
		void	setOnSocketEventListener(IClientSocket::OnSocketEvent *listener);

	// recv / send
	public:
		void			send(const Message &message);
		Message			receive(unsigned int sizeToRead);
		unsigned int	nbBytesToRead(void) const;

	// slots
	private slots:
		void	bytesWritten(qint64 nbBytes);
		void	markAsReadable(void);
		void	close(void);

	// attributes
	private:
		QUdpSocket	*mQUdpSocket;
		bool		mIsReadable;

		IClientSocket::OnSocketEvent	*mListener;

};

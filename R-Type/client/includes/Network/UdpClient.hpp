#pragma once

#include "IClientSocket.hpp"
#include <memory>
#include <QtNetwork/qudpsocket.h>

class UdpClient : public QObject, public IClientSocket{

	Q_OBJECT

	// ctor - dtor
	public:
		UdpClient(void);
		~UdpClient(void);

	// coplien form
	private:
		UdpClient(UdpClient const &) {}
		UdpClient const	&operator=(UdpClient const &) { return *this; }

		// start-stop
	public:
		void	connect(const std::string &addr, int port);
		void	initFromSocket(void *socket, const std::string &addr, int port);
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
		std::shared_ptr<QUdpSocket>	mQUdpSocket;
		bool						mIsReadable;

		IClientSocket::OnSocketEvent	*mListener;
};

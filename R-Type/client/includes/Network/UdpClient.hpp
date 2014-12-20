#pragma once

#include "IClientSocket.hpp"
#include "NoCopyable.hpp"
#include <memory>
#include <QtNetwork/qudpsocket.h>

class UdpClient : public QObject, public NoCopyable, public IClientSocket{

	Q_OBJECT

	// ctor - dtor
	public:
		UdpClient(void);
		~UdpClient(void);

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

	//
	public:
		const std::string 	&getAddr(void) const;
		int 				getPort(void) const;

	// attributes
	private:
		std::shared_ptr<QUdpSocket>	mQUdpSocket;
		bool						mIsReadable;
		std::string						mAddr;
		int								mPort;

		IClientSocket::OnSocketEvent	*mListener;
};

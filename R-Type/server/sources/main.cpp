#include "WindowsTcpClient.hpp"
#include "WindowsTcpServer.hpp"
#include <memory>
#include <iostream>

class TestServer : public IServerSocket::OnSocketEvent, public IClientSocket::OnSocketEvent {

	public:
		TestServer(void) {
			server.createServer(4242, 1024);
			server.setOnSocketEventListener(this);
		}

		void	onBytesWritten(IClientSocket *, unsigned int nbBytes) {
			std::cout << "byte written: " << nbBytes << std::endl;
		}

		void	onSocketReadable(IClientSocket *socket, unsigned int) {
			IClientSocket::Message message = socket->receive(1024);

			message.msg.push_back('\0');
			std::cout << "receive: " << message.msg.data() << std::endl;

			std::string str = "message received!";
			message.msg.clear();
			std::copy(str.begin(), str.end(), back_inserter(message.msg));
			message.msgSize = str.size();
			socket->send(message);
		}

		void	onSocketClosed(IClientSocket *) {
			std::cout << "socket closed" << std::endl;
		}

		void	onNewConnection(IServerSocket *socket) {
			std::cout << "new connection" << std::endl;
			client = socket->getNewClient();
			client->setOnSocketEventListener(this);
		}

		std::shared_ptr<IClientSocket> client;
		WindowsTcpServer server;

};

int main(void) {
	TestServer server;
	while (1);
	return 0;
}

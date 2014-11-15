#include "WindowsUdpClient.hpp"
#include <iostream>
/*
class TestClient : public IClientSocket::OnSocketEvent {

	public:
		TestClient(void) {
			client.connect("127.0.0.1", 4243);
			client.setOnSocketEventListener(this);

			IClientSocket::Message message;
			std::string str = "message received!";
			message.msg.clear();
			std::copy(str.begin(), str.end(), back_inserter(message.msg));
			message.msgSize = str.size();
			message.host = "127.0.0.1";
			message.port = 4242;
			client.send(message);
		}

		void	onBytesWritten(IClientSocket *, unsigned int nbBytes) {
			std::cout << "byte written: " << nbBytes << std::endl;
		}

		void	onSocketReadable(IClientSocket *socket, unsigned int) {
			IClientSocket::Message message = socket->receive(1024);

			message.msg.push_back('\0');
			std::cout << "receive msg from " << message.host << ":" << message.port << ": " << message.msg.data() << std::endl;

			std::string str = "message received!";
			message.msg.clear();
			std::copy(str.begin(), str.end(), back_inserter(message.msg));
			message.msgSize = str.size();
			socket->send(message);
		}

		void	onSocketClosed(IClientSocket *) {
			std::cout << "socket closed" << std::endl;
		}

		WindowsUdpClient client;

};

int main(void) {
	TestClient client;
	while (1);
	return 0;
}
*/

int main(void) {
	return 0;
}

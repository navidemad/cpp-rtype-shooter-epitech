#include "PlayerPacketBuilder.hpp"
#include "Network/UdpClient.hpp"

PlayerPacketBuilder::PlayerPacketBuilder(int port)
	: mCurrentHost(""), mCurrentPort(0), mCurrentState(PlayerPacketBuilder::State::HEADER), mCurrentCommand(nullptr), mClient(new UdpClient), mListener(nullptr)
{
	// A ADAPTER EN FONCTION DU RETOUR DE HANDSHAKE
	mClient->connect("127.0.0.1", 4242);
	mClient->setOnSocketEventListener(this);
}
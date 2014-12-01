#include "PlayerPacketBuilder.hpp"
#include "Network/UdpClient.hpp"

PlayerPacketBuilder::PlayerPacketBuilder(int port)
	: mCurrentHost(""), mCurrentPort(0), mCurrentState(PlayerPacketBuilder::State::HEADER), mCurrentCommand(nullptr), mClient(new UdpClient), mListener(nullptr)
{
	mClient->connect("127.0.0.1", port);
	mClient->setOnSocketEventListener(this);
}
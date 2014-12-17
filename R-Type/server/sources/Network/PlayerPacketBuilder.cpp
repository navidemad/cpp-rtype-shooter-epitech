#include "PlayerPacketBuilder.hpp"
#include "PortabilityBuilder.hpp"
#include "ICommand.hpp"
#include "CommandFactory.hpp"
#include "CommandException.hpp"
#include "Default.hpp"

PlayerPacketBuilder::PlayerPacketBuilder(int port) : 
mCurrentHost(""),
mCurrentPort(0),
mCurrentState(PlayerPacketBuilder::State::HEADER),
mCurrentCommand(nullptr),
mClient(PortabilityBuilder::getUdpClient()),
mListener(nullptr)
{
    mClient->connect(Config::Network::localAdress, port);
	mClient->setOnSocketEventListener(this);
}
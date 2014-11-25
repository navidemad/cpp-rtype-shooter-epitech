#include "RTypeClient.hpp"
#include "GUI/SFMLGraphic.hpp"
#include <iostream>

RTypeClient::RTypeClient()
: mCurrentId(RTypeClient::MENU), mEngine(this), mGui(new SFMLGraphic)
{
}

RTypeClient::~RTypeClient()
{

}

RTypeClient::RTypeClient(RTypeClient const &) : mEngine(this) {}

RTypeClient const	&RTypeClient::operator=(RTypeClient const &) { return *this; }

void	RTypeClient::run()
{
	mGui->init();

	while (mGui->isOpen())
	{
		mGui->update(); // update graphic engine
		mEngine.updateSystem();
		mGui->clear(); // clear graphic engine
	}
}

void	RTypeClient::setIdGame(unsigned int currentId)
{
	mCurrentId = currentId;
}

unsigned int	RTypeClient::getIdGame() const
{
	return mCurrentId;
}
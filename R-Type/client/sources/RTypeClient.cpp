#include "RTypeClient.hpp"
#include <iostream>

RTypeClient::RTypeClient()
: mCurrentId(RTypeClient::MENU), Engine(this)
{
}

RTypeClient::~RTypeClient()
{

}

RTypeClient::RTypeClient(RTypeClient const &) : Engine(this) {}

RTypeClient const	&RTypeClient::operator=(RTypeClient const &) { return *this; }

void	RTypeClient::run()
{
	
}

void	RTypeClient::setIdGame(unsigned int currentId)
{
	mCurrentId = currentId;
}

unsigned int	RTypeClient::getIdGame() const
{
	return mCurrentId;
}
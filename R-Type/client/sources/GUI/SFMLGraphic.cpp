#include "GUI/SFMLGraphic.hpp"

SFMLGraphic::SFMLGraphic()
	: mWindow(sf::VideoMode::getDesktopMode(), "toto")
{
	init();
}

SFMLGraphic::~SFMLGraphic()
{

}

bool	SFMLGraphic::drawSprite()
{
	return true;
}

bool	SFMLGraphic::drawFont()
{
	return true;
}

bool	SFMLGraphic::playSound(bool onLoop)
{
	return onLoop;
}

bool	SFMLGraphic::isOpen() const
{
	return mWindow.isOpen();
}

void	SFMLGraphic::handleEvent()
{
}

void	SFMLGraphic::init()
{
	mContentManager.loadTextures();
	mContentManager.loadFonts();
	mContentManager.loadSounds();
}

sf::Window const						&SFMLGraphic::getWindow() const
{
	return mWindow;
}

std::map<sf::Event, std::string> const	&SFMLGraphic::getKeyEvents() const
{
	return mKeyEvents;
}

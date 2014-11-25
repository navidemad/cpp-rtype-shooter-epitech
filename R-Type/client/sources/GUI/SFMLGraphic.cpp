#include "GUI/SFMLGraphic.hpp"

SFMLGraphic::SFMLGraphic()
	: mWindow(sf::VideoMode::getDesktopMode(), "toto")
{
	init();
}

SFMLGraphic::~SFMLGraphic()
{

}

bool	SFMLGraphic::drawSprite(uint32_t /*id*/, float /*delta*/, uint32_t /*x*/, uint32_t /*y*/)
{
	sf::Texture texture(mContentManager.getSprites()->getResource("1").getTexture());
	sf::IntRect rect(mContentManager.getSprites()->getResource("1").getFrame(1));
	sf::Sprite sprite(texture, rect);
	texture.setSmooth(true);
	sprite.setScale(sf::Vector2f(4, 4));
	mWindow.draw(sprite);
	return true;
}

bool	SFMLGraphic::drawFont(uint32_t /*id*/, uint32_t /*posX*/, uint32_t /*posY*/)
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

void	SFMLGraphic::show()
{
	mWindow.display();
}

void	SFMLGraphic::clear()
{
	mWindow.clear();
}

void	SFMLGraphic::init()
{
	mContentManager.loadTextures();
	mContentManager.loadSprites();
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

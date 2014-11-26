#include "GUI/SFMLGraphic.hpp"

SFMLGraphic::SFMLGraphic()
: mWindow(sf::VideoMode::getDesktopMode(), "R-type", sf::Style::Fullscreen), mInputManager(this)
{
}

SFMLGraphic::~SFMLGraphic()
{

}

bool	SFMLGraphic::drawSprite(std::string const &key, float /*delta*/, float x, float y)
{
	sf::Texture texture(mContentManager.getSprites()->getResource(key).getTexture());
	sf::IntRect rect(mContentManager.getSprites()->getResource(key).getFrame(0));
	sf::Sprite sprite(texture, rect);

	texture.setSmooth(true);
	
	sprite.setPosition(x, y);
	mWindow.draw(sprite);
	return true;
}

bool	SFMLGraphic::drawFont(std::string const &key, std::string const &str, float x, float y)
{
	sf::Text text;

	text.setFont(mContentManager.getFonts()->getResource(key));
	text.setString(str);
	text.setCharacterSize(128);
	text.setPosition(x, y);
	mWindow.draw(text);
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

void	SFMLGraphic::update()
{
	mInputManager.update();
}

void	SFMLGraphic::clear()
{
	mWindow.clear();
	mInputManager.clear();
}

void	SFMLGraphic::init()
{
	mContentManager.loadTextures();
	mContentManager.loadSprites();
	mContentManager.loadFonts();
	mContentManager.loadSounds();
	mWindow.setMouseCursorVisible(false);
}

sf::RenderWindow						&SFMLGraphic::getWindow()
{
	return mWindow;
}

/*
std::map<sf::Event, std::string> const	&SFMLGraphic::getKeyEvents() const
{
	return mKeyEvents;
}
*/

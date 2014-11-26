#include "GUI/SFMLGraphic.hpp"

std::shared_ptr<IGraphic>	SFMLGraphic::mInstance = nullptr;

SFMLGraphic::SFMLGraphic()
: mWindow(sf::VideoMode::getDesktopMode(), "R-type", sf::Style::Fullscreen), mInputManager(this)
{
}

SFMLGraphic::~SFMLGraphic()
{

}

std::shared_ptr<IGraphic>	SFMLGraphic::getInstance()
{
	if (mInstance == nullptr)
		mInstance = std::shared_ptr<IGraphic>(new SFMLGraphic);
	return mInstance;
}

bool	SFMLGraphic::drawSprite(std::string const &key, float /*delta*/, float x, float y)
{
	mContentManager.getSprites()->getResource(key).getSprite(0).setPosition(x, y);
	mWindow.draw(mContentManager.getSprites()->getResource(key).getSprite(0));
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

bool	SFMLGraphic::playSound(std::string const &key, bool onLoop)
{
	mContentManager.getSounds()->getResource(key).setLoop(onLoop);
	mContentManager.getSounds()->getResource(key).play();
	return true;
}

bool	SFMLGraphic::isOpen() const
{
	return mWindow.isOpen();
}

void	SFMLGraphic::handleEvent()
{
}

bool	SFMLGraphic::isPressed(std::string key)
{
	return mInputManager.isPressed(key);
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

sf::RenderWindow	&SFMLGraphic::getWindow()
{
	return mWindow;
}

/*
std::map<sf::Event, std::string> const	&SFMLGraphic::getKeyEvents() const
{
	return mKeyEvents;
}
*/

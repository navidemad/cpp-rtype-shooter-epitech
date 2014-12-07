#include "GUI/SFMLGraphic.hpp"

std::shared_ptr<IGraphic>	SFMLGraphic::mInstance = nullptr;

SFMLGraphic::SFMLGraphic()
	: mWindow(sf::VideoMode::getDesktopMode(), "R-type", sf::Style::Fullscreen), mInputManager(this), mMusicCurrentKey("")
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

bool	SFMLGraphic::drawSprite(std::string const &key, uint64_t delta, float x, float y, uint32_t id)
{
	// set time elapse by id
	if (!mIdTimeElapse.count(id))
		mIdTimeElapse[id] = 0;
	mIdTimeElapse[id] += delta;

	// set index of frame sprite
	uint32_t index;
	if (mContentManager.getSprites()->getResource(key).isLoop())
		index = mContentManager.getSprites()->getResource(key).getSize() * ((mIdTimeElapse[id] / 1000) % 1000) / 1000;
	else
		index = mContentManager.getSprites()->getResource(key).getCurrentIndex();
	mContentManager.getSprites()->getResource(key).setCurrentIndex(index);

	// set position of sprite
	mContentManager.getSprites()->getResource(key).getSprite(mContentManager.getSprites()->getResource(key).getCurrentIndex()).setPosition(x, y);

	// draw sprite on window
	mWindow.draw(mContentManager.getSprites()->getResource(key).getSprite(mContentManager.getSprites()->getResource(key).getCurrentIndex()));
	return true;
}

bool	SFMLGraphic::drawFont(std::string const &key, std::string const &str, float x, float y, uint32_t size = 128)
{
	sf::Text text;

	text.setFont(mContentManager.getFonts()->getResource(key));
	text.setString(str);
	text.setCharacterSize(size);
	text.setPosition(x, y);
	mWindow.draw(text);
	return true;
}

bool	SFMLGraphic::playMusic(std::string const &key, bool onLoop)
{
	if (key == mMusicCurrentKey || !mMusic.openFromFile(mContentManager.getMusics()->getResource(key)))
		return false;
	mMusic.setLoop(onLoop);
	mMusic.play();
	mMusicCurrentKey = key;
	return true;
}

bool	SFMLGraphic::playSound(std::string const &key, bool onLoop)
{
	mContentManager.getSounds()->getResource(key).sound.setBuffer(mContentManager.getSounds()->getResource(key).soundBuffer);
	mContentManager.getSounds()->getResource(key).sound.setLoop(onLoop);
	mContentManager.getSounds()->getResource(key).sound.play();
	return true;
}

void	SFMLGraphic::stopMusic()
{
	mMusic.stop();
}

void	SFMLGraphic::stopSound(std::string const &key)
{
	mContentManager.getSounds()->getResource(key).sound.stop();
}

void	SFMLGraphic::setVolume(std::string const &key, float volume)
{
	mContentManager.getSounds()->getResource(key).sound.setVolume(volume);
}

std::string	const		&SFMLGraphic::getInputText() const
{
	return mInputManager.getEnteredKey();
}

uint64_t	SFMLGraphic::getDelta()
{
	sf::Time	delta = mDeltaClock.restart();

	return delta.asMicroseconds();
}

void	SFMLGraphic::close()
{
	mWindow.close();
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
	mContentManager.loadMusics();
	mContentManager.loadSounds();
	mWindow.setMouseCursorVisible(false);
}

sf::RenderWindow	&SFMLGraphic::getWindow()
{
	return mWindow;
}

void				SFMLGraphic::setScale(std::string const &key, float sizeX, float sizeY)
{
	for (uint32_t i = 0; i < mContentManager.getSprites()->getResource(key).getSize(); ++i)
	{
		mContentManager.getSprites()->getResource(key).getSprite(0).setScale(sizeX, sizeY);
	}
}

/*
std::map<sf::Event, std::string> const	&SFMLGraphic::getKeyEvents() const
{
	return mKeyEvents;
}
*/

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GUI/SFMLGraphic.hpp"
#include "Default.hpp"

std::shared_ptr<IGraphic>	SFMLGraphic::mInstance = nullptr;

const unsigned int SFMLGraphic::TIME = 1000000;

SFMLGraphic::SFMLGraphic() :
	mVideoMode(sf::VideoMode(1280, 720)), mTitle(Config::Window::nameWindow), mStyle(sf::Style::Default),
	mWindow(mVideoMode, mTitle, mStyle), mInputManager(this), mMusicCurrentKey(""),
	mSoundVolume(Config::Audio::volume)
{
	mWindow.setActive(false);
}

SFMLGraphic::~SFMLGraphic()
{

}

const std::shared_ptr<IGraphic>	&SFMLGraphic::getInstance()
{
	if (mInstance == nullptr)
		mInstance = std::shared_ptr<IGraphic>(new SFMLGraphic);
	return mInstance;
}

bool	SFMLGraphic::drawSprite(std::string const &key, uint64_t delta, float x, float y, uint32_t id)
{
	auto sizeScreen = mWindow.getSize();

	// set time elapse by id
	if (!mIdTimeElapse.count(id))
		mIdTimeElapse[id] = 0;
	mIdTimeElapse[id] += delta;

	// set index of frame sprite
	uint32_t index;
	if (mContentManager.getSprites()->getResource(key).isLoop())
		index = (mContentManager.getSprites()->getResource(key).getSize() * (mIdTimeElapse[id] % TIME)) / TIME;
	else
		index = mContentManager.getSprites()->getResource(key).getCurrentIndex();
	mContentManager.getSprites()->getResource(key).setCurrentIndex(index);

	// set position of sprite
	mContentManager.getSprites()->getResource(key).getSprite(mContentManager.getSprites()->getResource(key).getCurrentIndex())
		.setPosition((static_cast<float>(sizeScreen.x) / 1920.f)* x, (static_cast<float>(sizeScreen.y) / 1080.f) * y);

	mContentManager.getSprites()->getResource(key).getSprite(mContentManager.getSprites()->getResource(key).getCurrentIndex())
		.setScale(static_cast<float>(sizeScreen.x) / 1920.f, static_cast<float>(sizeScreen.y) / 1080.f);

	// draw sprite on window
	mWindow.draw(mContentManager.getSprites()->getResource(key).getSprite(mContentManager.getSprites()->getResource(key).getCurrentIndex()));
	return true;
}

bool	SFMLGraphic::drawFont(std::string const &key, std::string const &str, float x, float y, uint32_t size = 128)
{
	sf::Text text;
	auto sizeScreen = mWindow.getSize();

	text.setFont(mContentManager.getFonts()->getResource(key));
	text.setString(str);
	text.setCharacterSize(size);
	text.setPosition((static_cast<float>(sizeScreen.x) / 1920.f) * x, (static_cast<float>(sizeScreen.y) / 1080.f) * y);
	text.setScale(static_cast<float>(sizeScreen.x) / 1920.f, static_cast<float>(sizeScreen.y) / 1080.f);
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
	if (mContentManager.getSounds()->getResource(key).sound.getVolume() != mSoundVolume)
		mContentManager.getSounds()->getResource(key).sound.setVolume(mSoundVolume);
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

float	SFMLGraphic::getVolumeMusic() const
{
	return mMusic.getVolume();
}

void	SFMLGraphic::setVolumeMusic(float volume)
{
	mMusic.setVolume(volume);
}

float	SFMLGraphic::getVolumeSound(std::string const &key) const
{
	return mContentManager.getSounds()->getResource(key).sound.getVolume();
}

void	SFMLGraphic::setVolumeSound(float volume)
{
	mSoundVolume = volume;
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

bool	SFMLGraphic::isPressed(std::string const &key) const
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
	mWindow.setMouseCursorVisible(true);
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

void				SFMLGraphic::setStyle(uint32_t style)
{
	mStyle = style;
}

void				SFMLGraphic::updateWindow()
{
	static bool		one = false;

	if (mStyle != sf::Style::Default && !one)
	{
		mWindow.create(mVideoMode, mTitle, mStyle);
		one = !one;
	}
}

void				SFMLGraphic::setFPSMode(bool enable)
{
	mWindow.setFramerateLimit(enable ? 60 : 0);
}

/*
std::map<sf::Event, std::string> const	&SFMLGraphic::getKeyEvents() const
{
	return mKeyEvents;
}
*/

#include "GUI/TextureManager.hpp"
#include "GUI/SpriteManager.hpp"
#include "GUI/FontManager.hpp"
#include "Audio/SoundManager.hpp"
#include "GUI/ContentManager.hpp"

ContentManager::ContentManager()
	: mTextures(&TextureManager()), mSprites(&SpriteManager()), mFonts(&FontManager()), mSounds(&SoundManager())
{
}

ContentManager::~ContentManager()
{
}

void	ContentManager::loadTextures()
{
	mTextures->loadResources();
}

void	ContentManager::loadSprites()
{
	mTextures->loadResources();
}

void	ContentManager::loadFonts()
{
	mFonts->loadResources();
}

void	ContentManager::loadSounds()
{
	mSounds->loadResources();
}

std::map<std::string, sf::Sprite> const	&ContentManager::getTextures() const
{
	return mTextures->getResources();
}


std::vector<SpriteModel> const	&ContentManager::getSprites() const
{
	return mSprites->getResources();
}

std::map<std::string, sf::Font> const	&ContentManager::getFonts() const
{
	return mFonts->getResources();
}

std::map<std::string, sf::Sound> const	&ContentManager::getSounds() const
{
	return mSounds->getResources();
}

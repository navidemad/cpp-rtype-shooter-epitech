#include <memory>
#include "GUI/ContentManager.hpp"

ContentManager::ContentManager() :
	mTextures(TextureManager::getInstance()), 
	mSprites(SpriteManager::getInstance()), 
	mFonts(FontManager::getInstance()), 
	mSounds(SoundManager::getInstance())
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
	mSprites->loadResources();
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

std::vector<std::shared_ptr<SpriteModel>> const	&ContentManager::getSprites() const
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

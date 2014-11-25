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

std::shared_ptr<IResourceManager<sf::Texture>> const	&ContentManager::getTextures() const
{
	return mTextures;
}

std::shared_ptr<IResourceManager<SpriteModel>> const	&ContentManager::getSprites() const
{
	return mSprites;
}

std::shared_ptr<IResourceManager<sf::Font>> const		&ContentManager::getFonts() const
{
	return mFonts;
}

std::shared_ptr<IResourceManager<sf::Sound>> const		&ContentManager::getSounds() const
{
	return mSounds;
}

#include "GUI/ContentManager.hpp"

ContentManager::ContentManager()
{
}

ContentManager::~ContentManager()
{
}

void	ContentManager::loadTextures()
{
}

void	ContentManager::loadFonts()
{
}

void	ContentManager::loadSounds()
{
}

std::map<std::string, sf::Sprite> const	&ContentManager::getTextures() const
{
	return mTextures;
}

std::map<std::string, sf::Font> const	&ContentManager::getFonts() const
{
	return mFonts;
}

std::map<std::string, sf::Sound> const	&ContentManager::getSounds() const
{
	return mSounds;
}

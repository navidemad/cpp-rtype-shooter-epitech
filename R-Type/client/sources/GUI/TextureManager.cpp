#include "GUI/TextureManager.hpp"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

void		TextureManager::loadResources()
{

}

void		TextureManager::unloadResources()
{

}

std::map<std::string, sf::Sprite> const		&TextureManager::getResources() const
{
	return mListResources;
}

#include <fstream>
#include "GUI/TextureManager.hpp"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

void		TextureManager::loadResources()
{
	std::ifstream	resourceFile;

	resourceFile.open("");
	resourceFile.close();
}

void		TextureManager::unloadResources()
{
	mListResources.clear();
}

std::map<std::string, sf::Sprite> const		&TextureManager::getResources() const
{
	return mListResources;
}

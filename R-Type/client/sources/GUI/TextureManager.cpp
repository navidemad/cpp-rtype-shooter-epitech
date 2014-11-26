#include <fstream>
#include "GUI/TextureManager.hpp"

std::shared_ptr<TextureManager>	TextureManager::mInstance = nullptr;

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

std::shared_ptr<TextureManager>	TextureManager::getInstance(void)
{
    if (mInstance == nullptr)
        mInstance = std::shared_ptr<TextureManager>(new TextureManager);
	return mInstance;
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

sf::Texture	&TextureManager::getResource(std::string const &key)
{
	return mListResources.at(key);
}

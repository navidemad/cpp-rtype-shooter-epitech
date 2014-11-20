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
		mInstance = std::shared_ptr<TextureManager>();
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

std::map<std::string, sf::Sprite> const		&TextureManager::getResources() const
{
	return mListResources;
}

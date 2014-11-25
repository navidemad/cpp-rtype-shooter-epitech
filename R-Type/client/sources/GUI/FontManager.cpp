#include "GUI/FontManager.hpp"

std::shared_ptr<FontManager>	FontManager::mInstance = nullptr;

FontManager::FontManager()
{

}

FontManager::~FontManager()
{

}

std::shared_ptr<FontManager>	FontManager::getInstance()
{
    if (mInstance == nullptr)
        mInstance = std::shared_ptr<FontManager>(new FontManager);
    return mInstance;
}

void	FontManager::loadResources()
{

}

void	FontManager::unloadResources()
{

}

sf::Font const	&FontManager::getResource(std::string const &key) const
{
	return mListResources.at(key);
}

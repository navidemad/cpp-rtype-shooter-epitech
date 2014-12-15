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

void	FontManager::loadResources(std::string const &key, std::string const &path)
{
	sf::Font font;

	if (!font.loadFromFile(path))
		throw std::runtime_error("Failed to load fonts...");
	mListResources.insert(std::pair<std::string, sf::Font>(key, font));
}

void	FontManager::unloadResources()
{

}

sf::Font	&FontManager::getResource(std::string const &key)
{
	return mListResources.at(key);
}

#include "GUI/FontManager.hpp"

FontManager::FontManager()
{

}

FontManager::~FontManager()
{

}

void	FontManager::loadResources()
{

}

void	FontManager::unloadResources()
{

}

std::map<std::string, sf::Font> const	&FontManager::getResources() const
{
	return mListResources;
}

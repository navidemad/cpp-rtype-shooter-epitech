#include <fstream>
#include "Audio/SoundManager.hpp"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

void	SoundManager::loadResources()
{
	std::ifstream	resourceFile;

	resourceFile.open("");
	resourceFile.close();
}

void	SoundManager::unloadResources()
{
	mListResources.clear();
}

std::map<std::string, sf::Sound> const	&SoundManager::getResources() const
{
	return mListResources;
}

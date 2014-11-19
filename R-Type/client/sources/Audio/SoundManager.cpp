#include "Audio/SoundManager.hpp"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

void	SoundManager::loadResources()
{

}

void	SoundManager::unloadResources()
{

}

std::map<std::string, sf::Sound> const	&SoundManager::getResources() const
{
	return mListResources;
}

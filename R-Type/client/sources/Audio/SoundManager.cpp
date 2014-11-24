#include <algorithm>
#include <fstream>
#include "Audio/SoundManager.hpp"

std::shared_ptr<SoundManager>	SoundManager::mInstance = nullptr;

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

std::shared_ptr<SoundManager>	SoundManager::getInstance()
{
    if (mInstance.get() == nullptr)
        mInstance = std::shared_ptr<SoundManager>(new SoundManager);
    return mInstance;
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

#include <algorithm>
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

void	SoundManager::loadResources(std::string const &key, std::string const &path)
{
	if (mListResources.count(key))
		return ;
	sf::sSound ssound;
	if (!ssound.soundBuffer.loadFromFile(path))
		throw std::runtime_error("Failed to load sound...");
	ssound.sound.setBuffer(ssound.soundBuffer);
	mListResources[key] = ssound;
}

void	SoundManager::unloadResources()
{
	mListResources.clear();
}

sf::sSound	&SoundManager::getResource(std::string const &key)
{
	return mListResources.at(key);
}

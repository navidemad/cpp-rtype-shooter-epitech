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

void	SoundManager::loadResources()
{
	{
		sf::SoundBuffer	buffer;
		if (!buffer.loadFromFile("./assets/sounds/efx/sample00/0x8c.wav"))
			throw std::runtime_error("Failed to load sound...");
		sf::Sound sound;
		sound.setBuffer(buffer);
		mListResources.insert(std::pair<std::string, sf::Sound>("mgs", sound));
	}
}

void	SoundManager::unloadResources()
{
	mListResources.clear();
}

sf::Sound	&SoundManager::getResource(std::string const &key)
{
	return mListResources.at(key);
}

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
		sf::sSound ssound;
		if (!ssound.soundBuffer.loadFromFile("./assets/sounds/efx/se_ok00.wav"))
			throw std::runtime_error("Failed to load sound...");
		ssound.sound.setBuffer(ssound.soundBuffer);
		ssound.test = "init... ok ! ;)";
		mListResources["ok"] = ssound;
	}
	{
		sf::sSound ssound;
		if (!ssound.soundBuffer.loadFromFile("./assets/sounds/efx/se_option.wav"))
			throw std::runtime_error("Failed to load sound...");
		ssound.sound.setBuffer(ssound.soundBuffer);
		ssound.test = "init... ok ! ;)";
		mListResources["option"] = ssound;
	}
	{
		sf::sSound ssound;
		if (!ssound.soundBuffer.loadFromFile("./assets/sounds/efx/se_pause.wav"))
			throw std::runtime_error("Failed to load sound...");
		ssound.sound.setBuffer(ssound.soundBuffer);
		ssound.test = "init... ok ! ;)";
		mListResources["pause"] = ssound;
	}
	{
		sf::sSound ssound;
		if (!ssound.soundBuffer.loadFromFile("./assets/sounds/efx/se_pldead00.wav"))
			throw std::runtime_error("Failed to load sound...");
		ssound.sound.setBuffer(ssound.soundBuffer);
		ssound.test = "init... ok ! ;)";
		mListResources["pldead"] = ssound;
	}
}

void	SoundManager::unloadResources()
{
	mListResources.clear();
}

sf::sSound	&SoundManager::getResource(std::string const &key)
{
	return mListResources.at(key);
}

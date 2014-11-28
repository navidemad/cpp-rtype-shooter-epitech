#include "Audio/MusicManager.hpp"

std::shared_ptr<MusicManager>	MusicManager::mInstance = nullptr;

MusicManager::MusicManager()
{

}

MusicManager::~MusicManager()
{

}

std::shared_ptr<MusicManager>	MusicManager::getInstance()
{
	if (mInstance == nullptr)
		mInstance = std::shared_ptr<MusicManager>(new MusicManager);
	return mInstance;
}

void			MusicManager::loadResources()
{
	{
		sf::Music music;
		if (!music.openFromFile("./assets/musics/Touhou_8/[01] Eternal Night Vignette ~ Eastern Night.mp3"))
			throw std::runtime_error("Failed to load music");
		//mListResources.insert(std::pair<std::string, sf::Music>("menu", music));
	}
}

void			MusicManager::unloadResources()
{

}

sf::Music		&MusicManager::getResource(std::string const &key)
{
	return mListResources.at(key);
}

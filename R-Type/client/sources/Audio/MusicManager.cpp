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
		mListResources.insert(std::pair<std::string, std::string>("Eastern Night", "./assets/musics/Touhou_8/[01] Eternal Night Vignette ~ Eastern Night.ogg"));
	}
}

void			MusicManager::unloadResources()
{

}

std::string		&MusicManager::getResource(std::string const &key)
{
	return mListResources.at(key);
}

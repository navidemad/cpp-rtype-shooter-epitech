#include "Audio/MusicManager.hpp"

std::shared_ptr<MusicManager>	MusicManager::mInstance = nullptr;

MusicManager::MusicManager()
{

}

MusicManager::~MusicManager()
{

}

const std::shared_ptr<MusicManager>	&MusicManager::getInstance()
{
	if (mInstance == nullptr)
		mInstance = std::shared_ptr<MusicManager>(new MusicManager);
	return mInstance;
}

void			MusicManager::loadResources(std::string const &key, std::string const &path)
{
	mListResources.insert(std::pair<std::string, std::string>(key, path));
}

void			MusicManager::unloadResources()
{

}

std::string		&MusicManager::getResource(std::string const &key)
{
	return mListResources.at(key);
}

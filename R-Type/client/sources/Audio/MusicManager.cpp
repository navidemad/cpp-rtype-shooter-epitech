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

void			MusicManager::loadResources(std::string const &, std::string const &)
{
	mListResources.insert(std::pair<std::string, std::string>("Menu", "./assets/musics/Touhou_8/[01] Eternal Night Vignette ~ Eastern Night.ogg"));
	mListResources.insert(std::pair<std::string, std::string>("Game", "./assets/musics/Touhou_8/[02] Illusionary Night ~ Ghostly Eyes.ogg"));
	mListResources.insert(std::pair<std::string, std::string>("Boss", "./assets/musics/Touhou_8/[08] Retribution for the Eternal Night ~ Imperishable Night.ogg"));
}

void			MusicManager::unloadResources()
{

}

std::string		&MusicManager::getResource(std::string const &key)
{
	return mListResources.at(key);
}

#include "GUI/SpriteManager.hpp"

std::shared_ptr<SpriteManager>	SpriteManager::mInstance = nullptr;

SpriteManager::SpriteManager()
{

}

SpriteManager::~SpriteManager()
{

}

std::shared_ptr<SpriteManager>	SpriteManager::getInstance()
{
    if (mInstance == nullptr)
        mInstance = std::shared_ptr<SpriteManager>(new SpriteManager);
    return mInstance;
}

void			SpriteManager::loadResources()
{
	{
		SpriteModel model("assets/sprites/menu.png", 1, 1);
		mListResources.insert(std::pair<std::string, SpriteModel>("menu", model));
	}
	{
		SpriteModel model("assets/sprites/logo.png", 1, 1);
		mListResources.insert(std::pair<std::string, SpriteModel>("logo", model));
	}
	{
		SpriteModel model("assets/sprites/logoCharacter.png", 1, 1);
		mListResources.insert(std::pair<std::string, SpriteModel>("logoCharacter", model));
	}
	{
		SpriteModel model("assets/sprites/search_bar.png", 1, 1);
		mListResources.insert(std::pair<std::string, SpriteModel>("searchBar", model));
	}
	{
		SpriteModel model("assets/sprites/r-typesheet3.gif", 4, 4);
		mListResources.insert(std::pair<std::string, SpriteModel>("ball", model));
	}
}

void			SpriteManager::unloadResources()
{

}

SpriteModel		&SpriteManager::getResource(std::string const &key)
{
	return mListResources.at(key);
}

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
	SpriteModel model("assets/sprites/r-typesheet7.gif", 2, 6);
	mListResources.insert(std::pair<std::string, SpriteModel>("1", model));
}

void			SpriteManager::unloadResources()
{

}

SpriteModel const	&SpriteManager::getResource(std::string const &key) const
{
	return mListResources.at(key);
}

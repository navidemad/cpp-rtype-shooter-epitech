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

void							SpriteManager::loadResources()
{
	std::shared_ptr<SpriteModel> model(new SpriteModel("assets/sprites/r-typesheet7.gif"));
	mListResources.push_back(model);
}

void							SpriteManager::unloadResources()
{

}

std::vector<std::shared_ptr<SpriteModel>> const	&SpriteManager::getResources() const
{
	return mListResources;
}

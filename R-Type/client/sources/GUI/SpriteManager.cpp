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
		mInstance = std::shared_ptr<SpriteManager>();
	return mInstance;
}


void							SpriteManager::loadResources()
{

}

void							SpriteManager::unloadResources()
{

}

std::vector<SpriteModel> const	&SpriteManager::getResources() const
{
	return mListResources;
}

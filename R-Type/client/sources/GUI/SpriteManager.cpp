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

void			SpriteManager::loadResources(std::string const &key, std::string const &path)
{
	SpriteModel model(path, 1, 1);
	mListResources.insert(std::pair<std::string, SpriteModel>(key, model));
}

void			SpriteManager::loadResources(std::string const &key, std::string const &path, uint32_t columns, uint32_t lines, bool loop)
{
	SpriteModel model(path, columns, lines);
	model.setLoop(loop);
	mListResources.insert(std::pair<std::string, SpriteModel>(key, model));
}

void			SpriteManager::unloadResources()
{

}

SpriteModel		&SpriteManager::getResource(std::string const &key)
{
	return mListResources.at(key);
}

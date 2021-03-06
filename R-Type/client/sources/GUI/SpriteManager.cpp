#include "GUI/SpriteManager.hpp"

std::shared_ptr<SpriteManager>	SpriteManager::mInstance = nullptr;

SpriteManager::SpriteManager()
{

}

SpriteManager::~SpriteManager()
{

}

const std::shared_ptr<SpriteManager>	&SpriteManager::getInstance()
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

void			SpriteManager::loadResources(std::string const &key, std::string const &path,
												uint32_t columns, uint32_t lines,
												SpriteOffset const &so, bool loop)
{
	SpriteModel model(path, columns, lines, sf::IntRect(so.getRectLeft(),
														so.getRectTop(),
														so.getRectWidth(),
														so.getRectHeight()));
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

// NESTED CLASS: SPRITEOFFSET - BEGIN

SpriteManager::SpriteOffset::SpriteOffset(uint32_t rectLeft, uint32_t rectTop, uint32_t rectWidth, uint32_t rectHeight) :
	mRectLeft(rectLeft),
	mRectTop(rectTop),
	mRectWidth(rectWidth),
	mRectHeight(rectHeight)
{

}

SpriteManager::SpriteOffset::~SpriteOffset()
{

}

uint32_t	SpriteManager::SpriteOffset::getRectLeft() const
{
	return mRectLeft;
}

uint32_t	SpriteManager::SpriteOffset::getRectTop() const
{
	return mRectTop;
}

uint32_t	SpriteManager::SpriteOffset::getRectWidth() const
{
	return mRectWidth;
}

uint32_t	SpriteManager::SpriteOffset::getRectHeight() const
{
	return mRectHeight;
}

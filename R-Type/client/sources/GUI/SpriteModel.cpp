#include <iterator>
#include <memory>
#include "GUI/SpriteModel.hpp"

SpriteModel::SpriteModel(std::string const &filename)
	: mLoop(true), mFileName(filename), mCurrentIndex(0), mBegin(0), mEnd(0)
{
	init();
}

SpriteModel::~SpriteModel()
{

}

void		SpriteModel::init()
{
	mSprites.clear();
	if (!mTexture.loadFromFile(mFileName))
		throw std::exception("Failed on load from file");
	mTexture.setSmooth(true);
	mSprite.setTexture(mTexture);
	mSprite.scale(sf::Vector2f(2.0, 2.0));
	mSprites.push_back(mSprite);
}

uint32_t		SpriteModel::getCurrentIndex() const
{
	return mCurrentIndex;
}

bool	SpriteModel::isLoop() const
{
	return mLoop;
}

std::string const	&SpriteModel::getFileName() const
{
	return mFileName;
}

sf::Sprite const	&SpriteModel::getSprite() const
{
	uint32_t index = (mCurrentIndex < mSprites.size()) ? mCurrentIndex : 0;
	//	if (mLoop)
	//		mCurrentIndex = (mCurrentIndex < mEnd) ? (mCurrentIndex + 1) : mBegin;
	if (mSprites.empty())
		return sf::Sprite();
	return (mSprites[index]);
}

void	SpriteModel::setAnims(uint32_t begin, uint32_t end)
{
	mBegin = begin;
	mEnd = end;
	mCurrentIndex = mBegin;
}

void	SpriteModel::setAnims(std::vector<sf::Sprite>::iterator begin, std::vector<sf::Sprite>::iterator end)
{
	mBegin = std::distance(mSprites.begin(), begin);
	mEnd = std::distance(mSprites.end(), end);
	mCurrentIndex = mBegin;
}

void	SpriteModel::setCurrentIndex(uint32_t currentIndex)
{
	mCurrentIndex = currentIndex;
}

void	SpriteModel::setLoop(bool enable)
{
	mLoop = enable;
}

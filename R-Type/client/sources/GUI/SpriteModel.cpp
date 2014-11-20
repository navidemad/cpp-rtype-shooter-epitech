#include <iterator>
#include "GUI/SpriteModel.hpp"

SpriteModel::SpriteModel()
	: mLoop(true), mIndex(0), mBegin(0), mEnd(0)
{

}

SpriteModel::~SpriteModel()
{

}

uint32_t	SpriteModel::getCurrentIndex() const
{
	return mIndex;
}

bool	SpriteModel::isLoop() const
{
	return mLoop;
}

void	SpriteModel::setAnims(uint32_t begin, uint32_t end)
{
	mBegin = begin % mSprites.size();
	mEnd = end % mSprites.size();
	mIndex = mBegin;
}

void	SpriteModel::setAnims(std::vector<sf::Sprite>::iterator begin, std::vector<sf::Sprite>::iterator end)
{
	mBegin = std::distance(mSprites.begin(), begin) % mSprites.size();
	mEnd = std::distance(mSprites.end(), end) % mSprites.size();
	mIndex = mBegin;
}

void	SpriteModel::setLoop(bool enable)
{
	mLoop = enable;
}

sf::Sprite const	&SpriteModel::getSprite()
{
	if (mIndex == mEnd)
		mIndex = mBegin;
	return (mSprites[mIndex++]);
}

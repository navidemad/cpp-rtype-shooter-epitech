#include <iterator>
#include <memory>
#include "GUI/SpriteModel.hpp"

SpriteModel::SpriteModel(std::string const &filename, uint32_t lines, uint32_t columns) :
	mLoop(true), 
	mFileName(filename), 
	mCurrentIndex(0), 
	mBegin(0), 
	mEnd(0), 
	mLines(lines), 
	mColumns(columns), 
	mPosX(0),
	mPosY(0)
{
	if (mLines == 0)
		mLines = 1;
	if (mColumns == 0)
		mColumns = 1;
	init();
}

SpriteModel::~SpriteModel()
{

}

void		SpriteModel::init()
{
	mFrames.clear();

	// load file image
	if (!mTexture.loadFromFile(mFileName))
		throw std::exception("Failed on load from file");

	// set params and sprite
	mTexture.setSmooth(true);
	mSprite.setTexture(mTexture);

	// set container of frame rectangle
	sf::Vector2u size = mTexture.getSize();
	int rectWidth = size.x / mColumns;
	int rectHeight = size.y / mLines;
	for (uint32_t i = 0; i < mLines * mColumns; ++i)
	{
		sf::IntRect rect(i % rectWidth, i / rectWidth, rectWidth, rectHeight);
		mFrames.push_back(rect);
	}
	//mSprite.scale(sf::Vector2f(2.0, 2.0));
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
	return (mSprite);
}

sf::IntRect const	&SpriteModel::getIntRect() const
{
	return mFrames[0];
}

void	SpriteModel::setAnims(uint32_t begin, uint32_t end)
{
	mBegin = begin;
	mEnd = end;
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

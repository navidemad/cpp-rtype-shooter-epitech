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
	// load file image
	if (!mTexture.loadFromFile(mFileName))
		throw std::exception(); // faire une class SpriteModelException

	// set params and sprite
	mTexture.setSmooth(true);
	mSprite.setTexture(mTexture);

	// set container of frame rectangle
	sf::Vector2u size = mTexture.getSize();
	int rectWidth = size.x / mColumns;
	int rectHeight = size.y / mLines;

	for (uint32_t i = 0; i < mLines * mColumns; ++i)
	{
		sf::IntRect rect((i % rectWidth) * rectWidth, (i / rectWidth) * rectHeight, rectWidth, rectHeight);
		mFrames.push_back(rect);
	}
	mTexture.setSmooth(true);
	mSprite.scale(sf::Vector2f(4.0, 4.0));
	mSprite.setTextureRect(mFrames[0]);
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

sf::IntRect const	&SpriteModel::getFrame(uint32_t index) const
{
	return mFrames[index];
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

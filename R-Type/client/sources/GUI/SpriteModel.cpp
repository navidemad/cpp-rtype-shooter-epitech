#include <iterator>
#include <memory>
#include "GUI/SpriteModel.hpp"

SpriteModel::SpriteModel(std::string const &filename, uint32_t columns, uint32_t lines, sf::IntRect const &rect) :
	mRect(rect),
	mLoop(true), 
	mFileName(filename), 
	mCurrentIndex(0), 
	mBegin(0), 
	mEnd(0), 
	mColumns(columns),
	mLines(lines),
	mX(0),
	mY(0)
{
	if (mLines == 0)
		++mLines;
	if (mColumns == 0)
		++mColumns;
	init();
}

SpriteModel::SpriteModel(const SpriteModel &sm) :
	mTexture(sm.getTexture()), 
	mRect(sm.getRect()), 
	mLoop(sm.isLoop()), 
	mFileName(sm.getFileName()), 
	mCurrentIndex(sm.getCurrentIndex()), 
	mBegin(sm.getBegin()), 
	mEnd(sm.getEnd()), 
	mColumns(sm.getColumns()), 
	mLines(sm.getLines()), 
	mX(sm.getX()), 
	mY(sm.getY())
{
	init();
}

const SpriteModel &SpriteModel::operator=(const SpriteModel &sm)
{
	mTexture = sm.getTexture();
	mRect = sm.getRect();
	mLoop = sm.isLoop();
	mFileName = sm.getFileName();
	mCurrentIndex = sm.getCurrentIndex();
	mBegin = sm.getBegin();
	mEnd = sm.getEnd();
	mLines = sm.getLines();
	mColumns = sm.getColumns();
	mX = sm.getX();
	mY = sm.getY();
	init();
	return *this;
}

SpriteModel::~SpriteModel()
{

}

void		SpriteModel::init()
{
	// load file image
	if (!mTexture.loadFromFile(mFileName, mRect))
		throw std::runtime_error("failed to load texture"); // faire une class SpriteModelException

	// set params and sprite
	mTexture.setSmooth(true);
	mSprite.setTexture(mTexture);

	// set container of frame rectangle
	sf::Vector2u const size = mTexture.getSize();
	if (size == sf::Vector2u(0, 0))
		throw std::runtime_error("Prevents Division by zero");
	uint32_t rectWidth = size.x / mColumns;
	uint32_t rectHeight = size.y / mLines;

	// sprite generator
	uint32_t const n = mLines * mColumns;
	for (uint32_t i = 0; i < n; ++i)
	{
		sf::IntRect rect((i % rectWidth) * rectWidth, (i / rectWidth) * rectHeight, rectWidth, rectHeight);
		sf::Sprite sprite(mTexture, rect);
		mSprites.push_back(sprite);
	}
}

// GETTER FUNCTIONS : BEGIN
sf::Texture const	&SpriteModel::getTexture() const
{
	return mTexture;
}

sf::IntRect const	&SpriteModel::getRect() const
{
	return mRect;
}

sf::Sprite			&SpriteModel::getSprite(uint32_t index)
{
	return mSprites[index];
}

bool				SpriteModel::isLoop() const
{
	return mLoop;
}

std::string const	&SpriteModel::getFileName() const
{
	return mFileName;
}

uint32_t			SpriteModel::getCurrentIndex() const
{
	return mCurrentIndex;
}

uint32_t			SpriteModel::getBegin() const
{
	return mBegin;
}

uint32_t			SpriteModel::getEnd() const
{
	return mEnd;
}

uint32_t			SpriteModel::getLines() const
{
	return mLines;
}

uint32_t			SpriteModel::getColumns() const
{
	return mColumns;
}

uint32_t			SpriteModel::getX() const
{
	return mX;
}

uint32_t			SpriteModel::getY() const
{
	return mY;
}

uint32_t			SpriteModel::getSize() const
{
	return (mSprites.size());
}

// GETTER FUNCTIONS : END

void	SpriteModel::setAnims(uint32_t begin, uint32_t end)
{
	mBegin = begin;
	mEnd = end;
	mCurrentIndex = mBegin;
}

void	SpriteModel::setCurrentIndex(uint32_t currentIndex)
{
	mCurrentIndex = currentIndex % mSprites.size();
}

void	SpriteModel::setLoop(bool enable)
{
	mLoop = enable;
}

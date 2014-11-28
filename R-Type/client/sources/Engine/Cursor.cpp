

#include "Engine/Compenent/Cursor.hpp"
#include "Engine/Entity.hpp"

Cursor::Cursor() : Component(ComponentType::CURSOR), mBlocked(false)
{
	mCurrent = mListEntity.begin();
}

Cursor::~Cursor()
{
	mListEntity.clear();
}

void	Cursor::block()
{
	mBlocked = ((mBlocked) ? false : true);
}

bool	Cursor::isBlocked() const
{
	return mBlocked;
}

void	Cursor::next()
{
	if (!mBlocked)
	{
		++mCurrent;
		if (mCurrent == mListEntity.end())
			mCurrent = mListEntity.begin();
	}
}

void	Cursor::prev()
{
	if (!mBlocked)
	{
		if (mCurrent == mListEntity.begin())
			mCurrent = mListEntity.end();
		--mCurrent;
	}
}

void	Cursor::addEntity(unsigned int id)
{

	mListEntity.push_back(id);
	mCurrent = mListEntity.begin();
}

unsigned int	Cursor::getIdEntity()
{
	return (*mCurrent);
}

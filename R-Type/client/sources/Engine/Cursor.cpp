

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

bool	Cursor::next()
{
	if (!mBlocked)
	{
		std::list<unsigned int>::iterator it = mCurrent;

		++mCurrent;
		if (mCurrent == mListEntity.end())
			mCurrent = mListEntity.begin();

		if (mCurrent != it)
			return true;
	}
	return false;
}

bool	Cursor::prev()
{
	if (!mBlocked)
	{
		std::list<unsigned int>::iterator it = mCurrent;

		if (mCurrent == mListEntity.begin())
			mCurrent = mListEntity.end();
		--mCurrent;

		if (mCurrent != it)
			return true;
	}
	return false;
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

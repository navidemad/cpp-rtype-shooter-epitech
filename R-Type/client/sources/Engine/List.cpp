#include <iostream>
#include "Engine/Compenent/List.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Font.hpp"
#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "RTypeClient.hpp"

bool	List::hasTimeElapsed() const
{
	return mTimeElapsed > mCycle;
}

void	List::resetTimer()
{
	mTimeElapsed = 0;
}

void	List::updateTimer(uint32_t delta)
{
	mTimeElapsed += delta;
}


/*
void	List::process(Entity &entity, uint32_t delta)
{
	updateTimer(delta);

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("z"))
	{
		if (mListRoomButton.begin() == mCurrentRoom)
		{
			if (mListRoom.begin() != *(mListRoomButton.begin()))
			{
				std::list<information_room>::iterator it = std::find(mListRoom.begin(), mListRoom.end(), *(*(mListRoomButton.begin())));
				--it;

				for (unsigned int i = 0; i != mNbRoomButton || it != mListRoom.end(); ++i, ++it)
				{
					mListRoomButton[i] = it;
				}
			}
		}
		else
		{
			--mCurrentRoom;
		}

		resetTimer();
	}

	else if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("z"))
	{
		resetTimer();
	}
	else if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		resetTimer();
	}

	displayRoom(entity);
}
*/
/*
void		List::displayRoom(Entity &entity)
{
	Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));
	Font *sprite = static_cast<Font *>(entity.getSpecificComponent(ComponentType::FONT));

	unsigned int	x = pos->getX();
	unsigned int	y = pos->getY();

	for (unsigned int i = 0; mListRoomButton.size() != i || i != mNbRoomButton; ++i)
	{
		entity.getEntityManager()->getClient()->getGui()->drawFont(sprite->getFont(), (*(mListRoomButton[i])).mName, x, y, 100);
		y += 100;
	}
}*/

List::List(unsigned int const nbRoomButton) : Component(ComponentType::LIST), mListRoomButton(nbRoomButton), mNbRoomButton(nbRoomButton)
{
	mCycle = 100;
	mTimeElapsed = 0;
	mCurrentRoom = mListRoomButton.begin();
}


void	List::addRoom(const information_room &room)
{
	mListRoom.push_back(room);
	if (mListRoom.size() <= mNbRoomButton)
	{
		unsigned int i = 0;

		for (std::list<information_room>::iterator it = mListRoom.begin();
			it != mListRoom.end();
			++it, ++i)
		{
			mListRoomButton[i] = it;
		}

	}
}
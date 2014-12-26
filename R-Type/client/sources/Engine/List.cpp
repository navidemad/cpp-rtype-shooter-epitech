#include <iostream>
#include "Engine/Compenent/List.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Font.hpp"
#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "RTypeClient.hpp"

bool	List::hasTimeElapsed() const
{
	return mTimeElapsed / 1000 > mCycle;
}

void	List::resetTimer()
{
	mTimeElapsed = 0;
}

void	List::updateTimer(uint32_t delta)
{
	mTimeElapsed += delta;
}

List::List(void (RTypeClient::*fct)(std::string const &), unsigned int const nbRoomButton) : Component(ComponentType::LIST), mListRoomButton(nbRoomButton), mNbRoomButton(nbRoomButton)
{
	mFct = fct;
	mCycle = 100;
	mTimeElapsed = 0;
	mCurrentRoom = mListRoomButton.begin();
}

void	List::applyFunction(std::string const &str, RTypeClient *client)
{
	(client->*mFct)(str);
}

void	List::clear()
{
	mListRoom.clear();
	mListRoomButton.clear();
}


void	List::addRoom(const information_room &room)
{
	mListRoom.push_back(room);
	if (mListRoom.size() <= mNbRoomButton)
	{
		mListRoomButton.clear();

		for (std::list<information_room>::iterator it = mListRoom.begin(); it != mListRoom.end(); ++it)
		{
			mListRoomButton.push_back(it);
		}
		mCurrentRoom = mListRoomButton.begin();
	}
}
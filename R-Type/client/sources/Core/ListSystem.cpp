#include "Core/ListSystem.hpp"
#include "Engine/ComponentType.h"
#include "Engine/Entity.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Drawable.hpp"
#include "Engine/Compenent/Font.hpp"
#include "Engine/Compenent/List.hpp"
#include "Engine/ECSManager.hpp"
#include "GUI/IGraphic.hpp"
#include "RTypeClient.hpp"

#include <algorithm>
#include <iostream>

ListSystem::ListSystem()
{
	setComponentNeeded(ComponentType::FONT);
	setComponentNeeded(ComponentType::MOVABLE);
	setComponentNeeded(ComponentType::LIST);
}

void	ListSystem::displayRoom(Entity &entity, Font *font, Position *pos, List *list)
{
	uint32_t	x = static_cast<unsigned int>(pos->getX());
	uint32_t	y = static_cast<unsigned int>(pos->getY());

	std::vector<std::list<information_room>::iterator>::iterator it = list->mListRoomButton.begin();

	for (; list->mListRoomButton.end() != it; ++it)
	{
		if (list->mCurrentRoom == it)
		{
			entity.getEntityManager()->getClient()->getGui()->drawSprite("cursor", 0, static_cast<float>(x - 85) ,static_cast<float>(y + 30), entity.getId());
			list->applyFunction((*(*it)).mName, entity.getEntityManager()->getClient());
		}

		std::string output = (*(*it)).mName;
		output.resize(13);
		output += std::string(13 - output.size(), ' ') + std::to_string((*(*it)).mNbPlayerInRoom) + "/" + std::to_string((*(*it)).mNbPlayerInRoom);

		entity.getEntityManager()->getClient()->getGui()->drawFont(font->getFont(), output, static_cast<float>(x), static_cast<float>(y), 100);
		y += 100;
	}
}

void	ListSystem::process(Entity &entity, uint32_t delta)
{
	Position *pos		= static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));
	Font *font			= static_cast<Font *>(entity.getSpecificComponent(ComponentType::FONT));
	List *list			= static_cast<List *>(entity.getSpecificComponent(ComponentType::LIST));

	list->updateTimer(delta);
	
	if (list->mListRoom.empty())
		return;

	if (list->hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("z"))
	{
		if (list->mListRoomButton.front() == *list->mCurrentRoom)
		{
			information_room &f = list->mListRoom.front();
			information_room &s = *list->mListRoomButton.front();

			if (f != s)
			{
				std::list<information_room>::iterator it = std::find(list->mListRoom.begin(), list->mListRoom.end(), *(list->mListRoomButton.front()));
				--it;

				for (unsigned int i = 0; i < list->mListRoom.size() && i != list->mNbRoomButton && *it != list->mListRoom.back(); ++i, ++it)
				{
					list->mListRoomButton[i] = it;
				}
				list->mCurrentRoom = list->mListRoomButton.begin();
			}
		}
		else
		{
			--(list->mCurrentRoom);
		}

		list->resetTimer();
	}

	else if (list->hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("s"))
	{
		if (list->mListRoomButton.back() == *list->mCurrentRoom)
		{
			information_room &f = list->mListRoom.back();
			information_room &s = *list->mListRoomButton.back();
			if (f != s)
			{
				std::list<information_room>::iterator it = std::find(list->mListRoom.begin(), list->mListRoom.end(), *(*(list->mListRoomButton.begin())));
				++it;

				for (unsigned int i = 0; i != list->mListRoom.size() && i != list->mNbRoomButton && it != list->mListRoom.end(); ++i, ++it)
				{
					list->mListRoomButton[i] = it;
				}
			}
			
		}
		else
		{
			++(list->mCurrentRoom);
		}
		list->resetTimer();
	}
	
	else if (list->hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("action"))
	{
		list->resetTimer();
	}

	displayRoom(entity, font, pos, list);
}

#include <algorithm>
#include <stdexcept>
#include "Engine/Compenent/List.hpp"
#include "Engine/ComponentType.h"
#include "Engine/ECSManagerNetwork.hpp"
#include "Engine/Entity.hpp"

ECSManagerNetwork::ECSManagerNetwork()
{

}

void ECSManagerNetwork::OnDestroyResource(int id)
{
	mRemoveId.push_back(id);
}

void ECSManagerNetwork::OnEndGame(const std::string &/*name*/)
{

}
#include <iostream>

void ECSManagerNetwork::OnError(ICommand::Instruction instruction, ErrorStatus::Error err)
{
	switch (err)
	{
	case ErrorStatus::Error::OK:
		std::cout << "ok" << std::endl;
		break;
	case ErrorStatus::Error::KO:
		std::cout << "ko" << std::endl;
		break;
	default:
		std::cout << "bad" << std::endl;
	}
}

void ECSManagerNetwork::OnMoveResource(IResource::Type /*type*/, float /*x*/, float /*y*/, short /*angle*/, int /*id*/)
{

}

void ECSManagerNetwork::OnShowGame(const std::string &name, const std::string &/*levelName*/, int nbPlayer, int maxPlayer, int /*nbObserver*/, int /*maxObserver*/)
{
	try
	{
		Entity &entity = getEntityWithSpecificCompenent(ComponentType::LIST);

		List *list = static_cast<List *>(entity.getSpecificComponent(ComponentType::LIST));
		list->addRoom(information_room(name, nbPlayer, maxPlayer));
	}
	catch (std::runtime_error &error)
	{
	}
}

void ECSManagerNetwork::OnShowLevel(const std::string &/*name*/, const std::string &/*script*/)
{

}

void ECSManagerNetwork::OnTimeElapse(int64_t /*time*/)
{

}

void ECSManagerNetwork::OnUpdateScore(const std::string &/*name*/, int /*id*/, int /*score*/)
{

}

void ECSManagerNetwork::OnCloseSocket(void){
	
}
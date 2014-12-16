#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <iostream>
#include "Default.hpp"
#include "Engine/Compenent/List.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Drawable.hpp"
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
	getClient()->setIdGame(RTypeClient::Game::MENU);
}

void ECSManagerNetwork::OnError(ICommand::Instruction /*instruction*/, ErrorStatus::Error err)
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

void ECSManagerNetwork::OnMoveResource(IResource::Type /*type*/, float x, float y, short /*angle*/, int id)
{
	std::cout << "ECSManagerNetwork::OnMoveResource" << std::endl;
	if (!isEntityCreated(id + mFirstId))
	{
		std::cout << "isEntityCreated(id) = false ; create entity in (x:'" << x << "'; y:'" << y << "'')" << std::endl;
		createEntity(id + mFirstId);

		Entity &entity = getEntity(id + mFirstId);
		entity.addComponent(new Position((Config::Window::x / 100.f) * x, (Config::Window::y / 100.f) * y));
		entity.addComponent(new Drawable("ball"));
	}
	else
	{
		std::cout << "isEntityCreated(id) = true ; update entity to (x:'" << x << "'; y:'" << y << "'')" << std::endl;
		Entity &entity = getEntity(id + mFirstId);
		Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));

		pos->setX((Config::Window::x / 100.f) * x);
		pos->setY((Config::Window::y / 100.f) * y);
	}
}

void ECSManagerNetwork::OnShowGame(const std::string &name, const std::string &/*levelName*/, int nbPlayer, int maxPlayer, int /*nbObserver*/, int /*maxObserver*/)
{
	try
	{
		Entity &entity = getEntityWithSpecificCompenent(ComponentType::LIST);

		List *list = static_cast<List *>(entity.getSpecificComponent(ComponentType::LIST));
		list->addRoom(information_room(name, nbPlayer, maxPlayer));
	}
	catch (std::runtime_error &/*error*/)
	{
	}
}

void ECSManagerNetwork::OnShowLevel(const std::string &name, const std::string &script)
{
	std::cout << "ECSManagerNetwork::OnShowLevel - scriptName: '" << name << "'" << std::endl;
	getClient()->setLevel(name);
	getClient()->setScript(script);
}

void ECSManagerNetwork::OnTimeElapse(int64_t time)
{
	std::cout << "ECSManagerNetwork::OnTimeElapse - time: '" << time << "'" << std::endl;
}

void ECSManagerNetwork::OnUpdateScore(const std::string &name, int id, int score)
{
	std::cout << "ECSManagerNetwork::OnUpdateScore - name: '" << name << "' id: '" << id << "' score: '" << score << "'" << std::endl;
}

void ECSManagerNetwork::OnCloseSocket(void){
	
}

void ECSManagerNetwork::OnFailConnect(void){

}
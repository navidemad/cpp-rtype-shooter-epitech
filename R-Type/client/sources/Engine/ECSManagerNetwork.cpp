#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include "Default.hpp"
#include "Engine/Compenent/List.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Drawable.hpp"
#include "Engine/ComponentType.h"
#include "Engine/ECSManagerNetwork.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Compenent/Velocity.hpp"
#include "PortabilityBuilder.hpp"
#include "IResource.hpp"
#include "DynLibException.hpp"

ECSManagerNetwork::ECSManagerNetwork()
{
	mDLLoader[IResource::Type::PLAYER]  = "./../shared/entities/Player/Player";
	mDLLoader[IResource::Type::ENNEMY]  = "./../shared/entities/Monster/Monster";
	mDLLoader[IResource::Type::BULLET ] = "./../shared/entities/Ball/Ball";
}

void ECSManagerNetwork::OnDestroyResource(int id)
{
	mRemoveId.push_back(id);
}

void ECSManagerNetwork::OnEndGame(const std::string &/*name*/)
{
	getClient()->setIdGame(RTypeClient::Game::MENU);
	auto freeMemory = [](Component *component) { delete component; };

	try
	{
		for (unsigned int id = mFirstId;; ++id)
		{
			mLivingEntity.at(id) = false;
			std::for_each(mEntityComponent.at(id)->begin(), mEntityComponent.at(id)->end(), freeMemory);
			mEntityComponent.at(id)->clear();
			mEntityBitset.at(id) = 0;
		}
	}
	catch (...) { }
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

void ECSManagerNetwork::OnMoveResource(IResource::Type type, float x, float y, short angle, int id)
{
	try
	{
		if (!isEntityCreated(id + mFirstId))
		{
			createEntity(id + mFirstId);

			Entity &entity = getEntity(id + mFirstId);
			auto lib = PortabilityBuilder::getDynLib();
			try {
				lib->libraryLoad(mDLLoader[type]);
				if (lib->functionLoad("entry_point") == nullptr)
					return;
				auto ressource = reinterpret_cast<IResource*(*)(void)>(lib->functionLoad("entry_point"))();

				entity.addComponent(new Drawable(ressource->getName()));
				entity.addComponent(new Position((Config::Window::x / 100.f) * x, (Config::Window::y / 100.f) * y));
				if (type == IResource::Type::BULLET)
				{
					entity.addComponent(new Velocity(cos(angle), sin(angle), 200));
					getClient()->getGui()->playSound("shot");
				}
			}
			catch (const DynLibException& e) {
				std::cout << "Exception DynLibException caught: '" << e.what() << "'" << std::endl;
				// ATTENTION IL FAUT DELETE LENTITE SI LA DLL N'EXISTE PAS
				// si l'entité n'a pas bien été loadé
				// car apres dans le else d'en dessous tu fais getSpecificComponent
				// que tu reinterpret_cast en Position* du coup sa va te renvoyait nullptr (cf mon patch: Entity.cpp getSpecificComponent)
			}
		}
		else
		{
			Entity &entity = getEntity(id + mFirstId);
			Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));

			pos->setX((Config::Window::x / 100.f) * x);
			pos->setY((Config::Window::y / 100.f) * y);
		}
	}
	catch (...) { }
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
	catch (...) { }
}

void ECSManagerNetwork::OnShowLevel(const std::string &scriptName)
{
	std::cout << "ECSManagerNetwork::OnShowLevel - scriptName: '" << scriptName << "'" << std::endl;
	getClient()->setLevel(scriptName);
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
    std::cout << "ECSManagerNetwork::OnFailConnect" << std::endl;
}
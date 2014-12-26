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

std::map<IResource::Type, std::string> ECSManagerNetwork::mDLLoader{
    { IResource::Type::PLAYER, "./../shared/resources/player/player" },
    { IResource::Type::CASTER, "./../shared/resources/caster/caster" },
    { IResource::Type::MELEE, "./../shared/resources/melee/melee" },
    { IResource::Type::SUPER, "./../shared/resources/super/super" },
    { IResource::Type::BULLET, "./../shared/resources/bullet/bullet" }
};

ECSManagerNetwork::ECSManagerNetwork()
{

}

void ECSManagerNetwork::OnDestroyResource(int id)
{
    id += mFirstId + 1;

    try {
        mLivingEntity.at(id) = false;
        mRemoveId.push_back(id);
    }
    catch (std::out_of_range &/* */) {}
}

void ECSManagerNetwork::OnEndGame(const std::string &/*name*/)
{
    getClient()->setIdGame(RTypeClient::Game::MENU);

    try
    {
        for (unsigned int id = mFirstId + 1;; ++id)
        {
            mLivingEntity.at(id) = false;
            mRemoveId.push_back(id);
        }
    }
    catch (std::out_of_range &/* */) {}
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

#include "GUI/SFMLGraphic.hpp"

void ECSManagerNetwork::OnMoveResource(IResource::Type type, float x, float y, short angle, int id)
{
    id += mFirstId + 1;

    try
    {
        std::string pathDll = "";
        for (auto pair : mDLLoader)
        {
            if (type == pair.first)
            {
                pathDll = pair.second;
                break;
            }
        }
        if (pathDll == "") {
            std::cerr << "unhandled type requested: '" << type << "'" << std::endl;
            return;
        }
        if (!isEntityCreated(id))
        {
            auto lib = PortabilityBuilder::getDynLib();
            try {
                lib->libraryLoad(pathDll);

                void *entrypoint = lib->functionLoad("entry_point");
                if (entrypoint == nullptr)
                    return;
                auto resource = reinterpret_cast<IResource*(*)(void)>(entrypoint)();
                if (resource == nullptr)
                    return;

                std::pair<unsigned int, std::list<Component *>> elemToInsert;

                elemToInsert.first = id;
                elemToInsert.second.push_back(new Drawable(resource->getName()));
                /*
                auto sizeScreen = SFMLGraphic::getInstance()->getWindow().getSize();
                elemToInsert.second.push_back(new Position(
                (static_cast<float>(sizeScreen.x) / 1920.f) * x,
                (static_cast<float>(sizeScreen.y) / 1080) * y
                );
                */
                elemToInsert.second.push_back(new Position(x, y));
                if (type == IResource::Type::BULLET)
                {
                    elemToInsert.second.push_back(new Velocity(cos(angle), sin(angle), 200));
                    getClient()->getGui()->playSound("shot");
                }
                mAddEntity.push_back(elemToInsert);
                lib->libraryFree();
            }
            catch (const DynLibException& e) {
                std::cout << "Exception DynLibException caught: '" << e.what() << "'" << std::endl;
            }
        }
        else
        {
            Entity &entity = getEntity(id);
            Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));

            //auto sizeScreen = SFMLGraphic::getInstance()->getWindow().getSize();
            //pos->setX((static_cast<float>(sizeScreen.x) / 1920.f) * x);
            //pos->setY((static_cast<float>(sizeScreen.y) / 1080) * y);

            pos->setX(x);
            pos->setY(y);
        }
    }
    catch (...) {}
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
    catch (...) {}
}

void ECSManagerNetwork::OnShowLevel(const std::string &scriptName)
{
    getClient()->setLevel(scriptName);
}

void ECSManagerNetwork::OnTimeElapse(int64_t /* */)
{
}

void ECSManagerNetwork::OnUpdateScore(const std::string &/*name*/, int /*id*/, int /*score*/)
{
}

void ECSManagerNetwork::OnCloseSocket(void){

}

void ECSManagerNetwork::OnFailConnect(void){
    std::cout << "ECSManagerNetwork::OnFailConnect" << std::endl;
}

#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "Engine/Compenent/Button.hpp"
#include "RTypeClient.hpp"

Button::Button() : Component(ComponentType::BUTTON)
{

}

Button::~Button()
{

}

void	ButtonGame::process(Entity &entity)
{
	entity.getEntityManager()->getClient()->setIdGame(RTypeClient::RTYPE);
}
#include "Core/BackgroundSystem.hpp"
#include "Default.hpp"
#include "Engine/Compenent/Background.hpp"
#include "Engine/Compenent/Position.hpp"

BackgroundSystem::BackgroundSystem()
{
	setComponentNeeded(ComponentType::BACKGROUND);
}

BackgroundSystem::~BackgroundSystem()
{

}
#include <iostream>
void	BackgroundSystem::process(Entity &entity, uint32_t /**/)
{
	Background *background = static_cast<Background *>(entity.getSpecificComponent(ComponentType::BACKGROUND));

	if (background->getList().empty())
		return;

	Position *pos = background->getList().front();

	if (pos->getX() <= -(Config::Title::sizeTitleBackground))
	{
		unsigned int cptr = background->getList().size();

		pos->setX(pos->getX() + (cptr * Config::Title::sizeTitleBackground));
		background->getList().pop_front();
		background->getList().push_back(pos);
	}
}
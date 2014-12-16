#include "Engine/Compenent/Background.hpp"
#include "Engine/ComponentType.h"

Background::Background()
: Component(ComponentType::BACKGROUND)
{

}

Background::~Background()
{
}

void	Background::addBackground(Position *pos)
{
	if (pos != nullptr)
		mListBackground.push_back(pos);
}

std::list<Position *>	&Background::getList()
{
	return mListBackground;
}
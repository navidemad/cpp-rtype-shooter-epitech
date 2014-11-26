#include "Core/System.hpp"
#include "Engine/ComponentType.h"

System::System()
{

}

System::~System()
{

}

void	System::setComponentNeeded(ComponentType::Type newType)
{
	mComponentNeeded.set(newType, 1);
}
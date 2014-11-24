#include "Engine/System.hpp"
#include "Engine/ComponentType.h"

System::System()
{

}

System::~System()
{

}

inline void	System::setComponentNeeded(ComponentType::Type newType)
{
	mComponentNeeded.set(newType, 1);
}
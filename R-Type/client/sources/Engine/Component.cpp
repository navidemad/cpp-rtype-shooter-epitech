#include "Engine/Component.hpp"
#include "Engine/ComponentType.h"

Component::Component(const ComponentType::Type id)
: mCompenentId(id)
{

}

Component::~Component()
{

}

const ComponentType::Type Component::getComponentId() const
{
	return mCompenentId;
}
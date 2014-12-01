#include "Engine/Component.hpp"
#include "Engine/ComponentType.h"

Component::Component(const ComponentType::Type id)
: mCompenentId(id)
{

}

Component::~Component()
{

}

ComponentType::Type Component::getComponentId() const
{
	return mCompenentId;
}

void				Component::setComponentId(ComponentType::Type type)
{
	mCompenentId = type;
}
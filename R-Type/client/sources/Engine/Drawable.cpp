#include <string>
#include "Engine/ComponentType.h"
#include "Engine/Compenent/Drawable.hpp"

Drawable::Drawable(const std::string &name) : Component(ComponentType::DRAWABLE), mName(name)
{

}

Drawable::~Drawable()
{

}

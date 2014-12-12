#pragma once

#include "Engine/Component.hpp"
#include "Engine/ComponentType.h"

class Gameplay : public Component
{
public:
	Gameplay(ComponentType::Type type);
	virtual ~Gameplay() { }
};

class Fire : public Gameplay
{
public:
	Fire();
	~Fire();
};

class Up : public Gameplay
{
public:
	Up();
	~Up();
};

class Down : public Gameplay
{
public:
	Down();
	~Down();
};

class Left : public Gameplay
{
public:
	Left();
	~Left();
};

class Right : public Gameplay
{
public:
	Right();
	~Right();
};

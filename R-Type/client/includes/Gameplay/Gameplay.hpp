#pragma once

#include <cstdint>
#include "Engine/Component.hpp"
#include "Engine/ComponentType.h"

class Gameplay : public Component
{
public:
	Gameplay(ComponentType::Type type, uint32_t);
	virtual ~Gameplay() { }

public:
	bool	hasTimeElapsed() const;

public:
	void	resetTimer();
	void	addDelta(uint32_t);

private:
	uint32_t	mTimeElapsed;
	uint32_t	mCycle;
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

class Back : public Gameplay
{
public:
	Back();
	~Back();
};
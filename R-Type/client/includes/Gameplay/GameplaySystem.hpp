#pragma once

#include "Core/System.hpp"
#include "Engine/ComponentType.h"

class FireSystem : public System
{
public:
	FireSystem();
	~FireSystem();

public:
	void	process(Entity &, uint32_t /* */);
};

class DownSystem : public System
{
public:
	DownSystem();
	~DownSystem();

public:
	void	process(Entity &, uint32_t /* */);
};

class UpSystem : public System
{
public:
	UpSystem();
	~UpSystem();

public:
	void	process(Entity &, uint32_t /* */);
};

class RightSystem : public System
{
public:
	RightSystem();
	~RightSystem();

public:
	void	process(Entity &, uint32_t /* */);
};

class LeftSystem : public System
{
public:
	LeftSystem();
	~LeftSystem();

public:
	void	process(Entity &, uint32_t /* */);
};
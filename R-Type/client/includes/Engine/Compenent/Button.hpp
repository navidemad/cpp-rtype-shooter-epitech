#pragma once

#include "Engine/Entity.hpp"
#include "Engine/Component.hpp"
#include "Engine/ComponentType.h"

class Button : public Component
{
	// ctor - dtor
	public:
		Button(uint32_t);
		~Button();

	// coplien form
	private:
		Button(Button const &) : Component(ComponentType::BUTTON) {}
		Button const	&operator=(Button const &) { return *this; }

	protected:
		bool	hasTimeElapsed() const;
		void	resetTimer();
		void	updateTimer(uint32_t delta);

	public:
		virtual void	process(Entity &, uint32_t delta) = 0;

private:
	uint32_t	mTimeElapsed;
	uint32_t	mCycle;
};

class ButtonGame : public Button
{
	public:
		ButtonGame() : Button(100) { }
		~ButtonGame() { }

	public:
		void	process(Entity &, uint32_t delta);
};

class ButtonQuitGame : public Button
{
public:
	ButtonQuitGame() : Button(100) { }
	~ButtonQuitGame() { }

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonMenuGame : public Button
{
public:
	ButtonMenuGame() : Button(100) { }
	~ButtonMenuGame() { }

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonOption : public Button
{
public:
	ButtonOption() : Button(100) { }
	~ButtonOption() { }

public:
	void	process(Entity &, uint32_t delta);
};

class ButtonInput : public Button
{
public:
	ButtonInput(unsigned int entity) : Button(100), mEntity(entity) { }
	~ButtonInput() { }

public:
	void	process(Entity &, uint32_t delta);

public:
	unsigned int	getEntity() const;

private:
	unsigned int	mEntity;
};

class ButtonSearchMenu : public Button
{
	public:
		ButtonSearchMenu() : Button(100) {}
		~ButtonSearchMenu() {}
	public:
		void	process(Entity &, uint32_t delta);
};
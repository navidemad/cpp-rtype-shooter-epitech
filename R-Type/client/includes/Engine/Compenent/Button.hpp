#pragma once

#include "Engine/Entity.hpp"
#include "Engine/Component.hpp"
#include "Engine/ComponentType.h"

class Button : public Component
{
	// ctor - dtor
	public:
		Button();
		~Button();

	// coplien form
	private:
		Button(Button const &) : Component(ComponentType::BUTTON) {}
		Button const	&operator=(Button const &) { return *this; }

	public:
		virtual void	process(Entity &) = 0;
};

class ButtonGame : public Button
{
	public:
		ButtonGame() { }
		~ButtonGame() { }

	public:
		void	process(Entity &);
};

class ButtonQuitGame : public Button
{
public:
	ButtonQuitGame() { }
	~ButtonQuitGame() { }

public:
	void	process(Entity &);
};

class ButtonMenuGame : public Button
{
public:
	ButtonMenuGame() { }
	~ButtonMenuGame() { }

public:
	void	process(Entity &);
};

class ButtonOption : public Button
{
public:
	ButtonOption() { }
	~ButtonOption() { }

public:
	void	process(Entity &);
};
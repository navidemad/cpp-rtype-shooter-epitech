#pragma once

#include <list>

class SFMLGraphic;

class InputManager
{
public: //ctor dtor
	InputManager(SFMLGraphic *);
	~InputManager();

public:
	void		clear();
	void		update();
	void		init();

private:
	std::list<sf::Event>	mPoolEvent;
	SFMLGraphic				*mGraphic;
};
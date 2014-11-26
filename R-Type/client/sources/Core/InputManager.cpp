#include <SFML/Graphics.hpp>
#include <algorithm>
#include "GUI/SFMLGraphic.hpp"
#include "Core/InputManager.hpp"

InputManager::InputManager(SFMLGraphic *graphic) : mGraphic(graphic) { }
InputManager::~InputManager() { }


void	InputManager::clear()
{
	mPoolEvent.clear();
}

void	InputManager::update()
{
	sf::Event	currentEvent;

	while (mGraphic->getWindow().pollEvent(currentEvent))
	{
		if (currentEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			mGraphic->getWindow().close();
		else
			mPoolEvent.push_back(currentEvent);
	}
}

void	InputManager::init()
{
}
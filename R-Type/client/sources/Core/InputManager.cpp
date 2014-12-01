#include <SFML/Graphics.hpp>
#include <algorithm>
#include "GUI/SFMLGraphic.hpp"
#include "Core/InputManager.hpp"

InputManager::InputManager(SFMLGraphic *graphic) : mGraphic(graphic)
{
	mKeyboard[sf::Keyboard::Down] = "down";
	mKeyboard[sf::Keyboard::Up] =	"up";
	mKeyboard[sf::Keyboard::Return] = "action";
	mKeyboard[sf::Keyboard::Space] = "action";
	mKeyboard[sf::Keyboard::Escape] = "back";
	mKeyboard[sf::Keyboard::BackSpace] = "delete";

	mPoolEvent["down"] = false;
	mPoolEvent["up"] = false;
	mPoolEvent["action"] = false;
	mPoolEvent["back"] = false;
	mPoolEvent["delete"] = false;

	mEnteredKey = "";
}

InputManager::~InputManager() { }

void	InputManager::pressedKey(sf::Keyboard::Key keycode)
{
	std::string key = mKeyboard[keycode];

	mPoolEvent[key] = true;
}

void	InputManager::releasedKey(sf::Keyboard::Key keycode)
{
	std::string &key = mKeyboard[keycode];

	mPoolEvent[key] = false;
}

std::string const &InputManager::getEnteredKey() const
{
	return mEnteredKey;
}

bool	InputManager::isPressed(std::string key)
{
	return mPoolEvent[key];
}

void	InputManager::clear()
{
	mEnteredKey = "";
}

#include <iostream>
void	InputManager::enteredKey(char c)
{
	if (c > 31)
		mEnteredKey += c;
}

void	InputManager::update()
{
	sf::Event	currentEvent;

	while (mGraphic->getWindow().pollEvent(currentEvent))
	{
		if (sf::Event::Closed || (sf::Event::KeyPressed == currentEvent.type && currentEvent.key.code == sf::Keyboard::Escape))
			mGraphic->close();
		if (sf::Event::KeyPressed == currentEvent.type)
		{
			pressedKey(currentEvent.key.code);
		}
		else if (sf::Event::KeyReleased == currentEvent.type)
		{
			releasedKey(currentEvent.key.code);
		}
		if (sf::Event::TextEntered == currentEvent.type)
		{
			enteredKey(currentEvent.text.unicode);
		}
	}
}

void	InputManager::init()
{
}
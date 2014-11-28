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

	mPoolEvent["down"] = false;
	mPoolEvent["up"] = false;
	mPoolEvent["action"] = false;
	mPoolEvent["back"] = false;
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

bool	InputManager::isPressed(std::string key)
{
	return mPoolEvent[key];
}

void	InputManager::clear()
{
//	mPoolEvent.clear();
}

void	InputManager::update()
{
	sf::Event	currentEvent;

	while (mGraphic->getWindow().pollEvent(currentEvent))
	{
		if (sf::Event::Closed || (sf::Event::KeyPressed == currentEvent.type && currentEvent.key.code == sf::Keyboard::Escape))
			mGraphic->close();
		if (sf::Event::KeyPressed == currentEvent.type)
			pressedKey(currentEvent.key.code);
		else if (sf::Event::KeyReleased == currentEvent.type)
			releasedKey(currentEvent.key.code);
	}
}

void	InputManager::init()
{
}
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "GUI/SFMLGraphic.hpp"
#include "Core/InputManager.hpp"

InputManager::InputManager(SFMLGraphic *graphic) : mGraphic(graphic)
{
	mKeyboard[sf::Keyboard::Down] = "down";
	mKeyboard[sf::Keyboard::Up] =	"up";
	mKeyboard[sf::Keyboard::Left] = "left";
	mKeyboard[sf::Keyboard::Right] = "right";
	mKeyboard[sf::Keyboard::Return] = "action";
	mKeyboard[sf::Keyboard::Space] = "action";
	mKeyboard[sf::Keyboard::Escape] = "back";
	mKeyboard[sf::Keyboard::BackSpace] = "delete";
	mKeyboard[sf::Keyboard::Z] = "z";
	mKeyboard[sf::Keyboard::S] = "s";
	mKeyboard[sf::Keyboard::Q] = "q";
	mKeyboard[sf::Keyboard::D] = "d";

	mPoolEvent["down"] = false;
	mPoolEvent["up"] = false;
	mPoolEvent["left"] = false;
	mPoolEvent["right"] = false;
	mPoolEvent["action"] = false;
	mPoolEvent["back"] = false;
	mPoolEvent["delete"] = false;
	mPoolEvent["z"] = false;
	mPoolEvent["a"] = false;
	mPoolEvent["q"] = false;
	mPoolEvent["d"] = false;

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

bool	InputManager::isPressed(const std::string &key) const
{
	return mPoolEvent.at(key);
}

void	InputManager::clear()
{
	mEnteredKey = "";
}

void	InputManager::enteredKey(char c)
{
	if (c > 31)
		mEnteredKey += c;
}

void	InputManager::update()
{
	sf::Event	currentEvent;

	try
	{
		if (mGraphic && mGraphic->getWindow().isOpen())
			while (mGraphic->getWindow().pollEvent(currentEvent))
			{
				if (sf::Event::Closed)
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
	catch (std::exception &/* */) { }
}

void	InputManager::init()
{
}
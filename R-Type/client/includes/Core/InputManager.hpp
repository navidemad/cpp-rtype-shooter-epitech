#pragma once

#include <list>
#include <string>

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

	void				pressedKey(sf::Keyboard::Key);
	void				releasedKey(sf::Keyboard::Key);
	bool				isPressed(const std::string &) const;
	std::string	const	&getEnteredKey() const;
	void				enteredKey(char);

private:
	std::map<std::string, bool>					mPoolEvent;
	std::map<sf::Keyboard::Key, std::string>	mKeyboard;
	SFMLGraphic									*mGraphic;
	std::string									mEnteredKey;
};
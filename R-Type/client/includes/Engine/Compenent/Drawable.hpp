#pragma once

#include <string>
#include "../Component.hpp"
#include "../ComponentType.h"

class Drawable : public Component
{
	// ctor - dtor
	public:
		Drawable(std::string);
		~Drawable();

	// coplien form
	private:
		Drawable(Drawable const &) : Component(ComponentType::DRAWABLE) {}
		Drawable const	&operator=(Drawable const &) { return *this; }

public:
	void				setName(std::string &name) { mName = name; }
	const std::string	&getName() const { return mName; }

private:
	std::string		mName;
};

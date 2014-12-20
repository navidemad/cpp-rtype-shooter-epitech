#pragma once

#include <string>
#include "../Component.hpp"
#include "../ComponentType.h"
#include "NoCopyable.hpp"

class Drawable : public NoCopyable, public Component
{
	// ctor - dtor
	public:
		Drawable(std::string);
		~Drawable();

    public:
	    void				setName(std::string &name) { mName = name; }
	    const std::string	&getName() const { return mName; }

    private:
	    std::string		mName;
};

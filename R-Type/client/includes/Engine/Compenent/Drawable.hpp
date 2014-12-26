#pragma once

#include <string>
#include "../Component.hpp"
#include "../ComponentType.h"
#include "NoCopyable.hpp"

class Drawable : public NoCopyable, public Component
{
	// ctor - dtor
	public:
		Drawable(const std::string &);
		~Drawable();

    public:
	    void				setName(const std::string &name) { mName = name; }
	    const std::string	&getName() const { return mName; }

    private:
	    std::string		mName;
};

#pragma once

#include "Engine/Component.hpp"
#include "NoCopyable.hpp"

class Script : public NoCopyable, public Component
{
    // ctor - dtor
    public:
		Script();
		~Script();

};

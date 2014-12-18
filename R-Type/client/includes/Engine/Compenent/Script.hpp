#pragma once

#include "Engine/Component.hpp"

class Script : public Component
{
    // ctor - dtor
    public:
		Script();
		~Script();

    // copy operators
    public:
		Script(const Script &) = delete;
		Script(Script &&) = delete;
		const Script &operator=(const Script &) = delete;
		const Script &operator=(Script &&) = delete;
};

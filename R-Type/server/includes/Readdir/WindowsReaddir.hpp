#pragma once

#include "IReaddir.hpp"

class WindowsReaddir : public IReaddir
{
	public:
		WindowsReaddir();
		~WindowsReaddir();
};

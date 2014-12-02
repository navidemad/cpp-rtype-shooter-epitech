#pragma once

#include "IReaddir.hpp"

class UnixReaddir : public IReaddir
{
	public:
		UnixReaddir();
		~UnixReaddir();
};

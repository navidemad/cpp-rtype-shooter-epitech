#pragma once

#include "IReaddir.hpp"

class UnixReaddir : public IReaddir
{
	public:
		UnixReaddir();
		~UnixReaddir();
	public:
		std::list<std::string> readFolder(std::string pathFolder);
};

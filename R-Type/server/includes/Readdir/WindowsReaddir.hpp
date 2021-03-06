#pragma once

#include "Config.hpp"
#include "IReaddir.hpp"

#include <list>

class WindowsReaddir : public IReaddir
{
	public:
		WindowsReaddir();
		~WindowsReaddir();
	public:
		std::list<std::string> readFolder(const std::string &folderName) const;
		std::wstring s2ws(const std::string& s) const;

};

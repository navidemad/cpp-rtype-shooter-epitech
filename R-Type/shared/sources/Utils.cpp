#include "Utils.hpp"
#include <iostream>
#include <algorithm>

void Utils::logInfo(const std::string &log) {
#ifdef _DEBUG
	std::cout << log << std::endl;
#endif
}

void Utils::logError(const std::string &log) {
#ifdef _DEBUG
	std::cerr << log << std::endl;
#endif
}

std::string Utils::basename(const std::string &pathname)
{
	return std::string(std::find_if(pathname.rbegin(), pathname.rend(),	Utils::MatchPathSeparator()).base(), pathname.end());
}

std::string Utils::removeExtension(const std::string &pathname)
{
	std::string::const_reverse_iterator	pivot = std::find(pathname.rbegin(), pathname.rend(), '.');
	return pivot == pathname.rend() ? pathname : std::string(pathname.begin(), pivot.base() - 1);
}
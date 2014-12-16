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

std::vector<std::string> Utils::split(const std::string& str, int delimiter(int)) {
	std::vector<std::string> result;
	auto e = str.end();
	auto i = str.begin();
	while (i != e) {
		i = find_if_not(i, e, delimiter);
		if (i == e) break;
		auto j = find_if(i, e, delimiter);
		result.push_back(std::string(i, j));
		i = j;
	}
	return result;
}

int Utils::iseol(int ch) {
	return ch == '\n';
}
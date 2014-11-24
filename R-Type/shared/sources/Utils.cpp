#include "Utils.hpp"
#include <iostream>

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

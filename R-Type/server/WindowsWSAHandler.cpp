#include "WindowsWSAHandler.hpp"
#include "SocketException.hpp"
#include <Winsock2.h>

int WindowsWSAHandler::nbInstances = 0;

void WindowsWSAHandler::init(void) {
	if (nbInstances == 0) {
		WORD wVersionRequested = MAKEWORD(2, 2);
		WSADATA wsaData;

		if (WSAStartup(wVersionRequested, &wsaData))
			throw SocketException("fail WSAStartup()");
	}

	++nbInstances;
}

void WindowsWSAHandler::cleanup(void) {
	--nbInstances;

	if (nbInstances == 0)
		WSACleanup();
}

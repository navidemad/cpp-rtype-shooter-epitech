#include "WindowsReaddir.hpp"
#include <iostream>
#include <string>

WindowsReaddir::WindowsReaddir(void) {
}

WindowsReaddir::~WindowsReaddir(void) {
}

std::list<std::string> WindowsReaddir::readFolder(std::string pathFolder) {
	std::list<std::string> files;

	HANDLE hFind;
	WIN32_FIND_DATA data;

	pathFolder += "\\*.*";
	hFind = FindFirstFile(s2ws(pathFolder).c_str(), &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (strcmp(reinterpret_cast<char*>(data.cFileName), ".") && strcmp(reinterpret_cast<char*>(data.cFileName), "..")) {
				const std::wstring ws = std::wstring(data.cFileName);			
				const std::string file(ws.begin(), ws.end());
				files.push_back(file);
			}
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
	return files;
}

std::wstring WindowsReaddir::s2ws(const std::string& s)
{
    int len;
    int slength = static_cast<int>(s.length() + 1);
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];

    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}
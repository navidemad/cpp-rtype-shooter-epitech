#include "WindowsReaddir.hpp"
#include <iostream>
#include <string>

WindowsReaddir::WindowsReaddir(void) {
}

WindowsReaddir::~WindowsReaddir(void) {
}

std::list<std::string> WindowsReaddir::readFolder(const std::string &folderName) const {
	std::list<std::string> files;

	HANDLE hFind;
	WIN32_FIND_DATA file_data;
	const std::string pattern = folderName + "/*";

	if ((hFind = FindFirstFile(s2ws(pattern).c_str(), &file_data)) != INVALID_HANDLE_VALUE) {
		do {
			const std::wstring ws = std::wstring(file_data.cFileName);
			const std::string file_name(ws.begin(), ws.end());
			const std::string full_file_name = folderName + "/" + file_name;
			const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

			if (file_name[0] == '.' || is_directory)
				continue;

			files.push_back(full_file_name);
		} while (FindNextFile(hFind, &file_data));
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
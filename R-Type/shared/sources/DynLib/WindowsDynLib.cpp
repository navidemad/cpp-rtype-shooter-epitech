#include "WindowsDynLib.hpp"
#include "DynLibException.hpp"

#include <iostream>
#include <direct.h>
#include <map>

const std::string WindowsDynLib::extension = ".dll";

WindowsDynLib::WindowsDynLib(void) : mDLLHandle(nullptr) {

}

WindowsDynLib::~WindowsDynLib(void) {
    libraryFree();
}

void    WindowsDynLib::libraryLoad(const std::string& libraryName) {
    std::string path = normalize(libraryName);

	if (!(mDLLHandle = ::LoadLibrary(s2ws(path).c_str())))
		throw DynLibException("Can't load the DLL - fail LoadLibrary(): " + path);
}

void    *WindowsDynLib::functionLoad(const std::string& functionName) const {
	if (mDLLHandle) {
		return (void *)GetProcAddress(mDLLHandle, functionName.c_str());
	}
    throw DynLibException("fail functionLoad()");
    return (NULL);
}

void    WindowsDynLib::libraryFree() {
	::FreeLibrary(mDLLHandle);
}

std::wstring WindowsDynLib::s2ws(const std::string& s) const
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

std::string WindowsDynLib::normalize(const std::string& libraryName) const {
  return libraryName + WindowsDynLib::extension;
}

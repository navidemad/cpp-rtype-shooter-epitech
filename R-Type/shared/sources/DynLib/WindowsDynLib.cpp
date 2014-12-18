#include "WindowsDynLib.hpp"
#include "DynLibException.hpp"

#include <iostream>
#include <direct.h>
#include <map>

const std::string WindowsDynLib::extension = ".dll";

void    WindowsDynLib::libraryLoad(const std::string& libraryName) {
    std::string path = libraryName + WindowsDynLib::extension;

	if (!(mDLLHandle = ::LoadLibrary(s2ws(path).c_str())))
        throw DynLibException("Can't load the DLL - fail LoadLibrary()");
}

void    *WindowsDynLib::functionLoad(const std::string& functionName) {
	if (mDLLHandle) {
		return (void *)GetProcAddress(mDLLHandle, functionName.c_str());
	}   
    throw DynLibException("fail functionLoad()");
    return (NULL);
}

void    WindowsDynLib::libraryFree() {
	::FreeLibrary(mDLLHandle);
}

std::wstring WindowsDynLib::s2ws(const std::string& s)
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

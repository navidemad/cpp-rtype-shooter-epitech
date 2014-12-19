#include "UnixDynLib.hpp"
#include "DynLibException.hpp"

const std::string UnixDynLib::extension = ".so";

void    UnixDynLib::libraryLoad(const std::string& libraryName) {
    std::string path = normalize(libraryName);

    if (!(mHandle = dlopen(path.c_str(), RTLD_LAZY)))
      throw DynLibException(dlerror());
    dlerror();
}

void*  UnixDynLib::functionLoad(const std::string& functionName) {
  char *error;
  void *tmp = dlsym(mHandle, functionName.c_str());

    if ((error = dlerror()) != NULL)
      throw DynLibException(error);
    return (tmp);
}

void    UnixDynLib::libraryFree() {
    if (mHandle)
        dlclose(mHandle);
}

std::string UnixDynLib::normalize(const std::string& libraryName) {
  std::string path = libraryName;
    if (path.length()) {
      auto it = path.end() - 1;
      if (*it == '/')
         path.erase(it);
    }
  auto found = path.find_last_of("/\\");
  if (found != std::string::npos) {
    path.insert(path.begin() + found + 1, 'l');
    path.insert(path.begin() + found + 2, 'i');
    path.insert(path.begin() + found + 3, 'b');
  }
  return path + UnixDynLib::extension;
}

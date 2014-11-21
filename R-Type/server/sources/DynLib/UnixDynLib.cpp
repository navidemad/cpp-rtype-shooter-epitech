#include "UnixDynLib.hpp"
#include "DynLibException.hpp"

void    UnixDynLib::libraryLoad(std::string& libraryName) {

    if (!(mHandle = dlopen(std::string(libName + EXT).c_str(), RTLD_LAZY)))
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

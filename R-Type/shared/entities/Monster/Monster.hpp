#pragma once

#include "../../includes/IResource.hpp"

#if defined (WIN32)
    #if defined (_MSC_VER)
        #pragma warning(disable: 4251)
    #endif
    #define MYLIB_EXPORT __declspec(dllexport)
#else
    #define MYLIB_EXPORT
#endif

class MYLIB_EXPORT Monster : public IResource {
public:
    Monster();
    ~Monster();
public:
	virtual double getSpeed(void) const;
private:
    double mSpeed;
};
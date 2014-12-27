#pragma once

#include <string>
#include <map>

#if defined (WIN32)
# if defined (_MSC_VER)
#  pragma warning(disable: 4251)
# endif
# define MYLIB_EXPORT __declspec(dllexport)
#else
# define MYLIB_EXPORT
#endif

struct MYLIB_EXPORT IResource {
	public:

		enum class Direction : char {
			LEFT	= 0x00,
			RIGHT	= 0x01,
			TOP		= 0x02,
			BOTTOM	= 0x03,
			UNKNOWN
		};

		enum Type {
            PLAYER      = 1 << 0,
            BULLET      = 1 << 1,
            BONUS       = 1 << 2,
            CASTER      = 1 << 3,
            MELEE       = 1 << 4,
            SUPER       = 1 << 5,
	        UNKNOWN     = 1 << 6
		};

                                    IResource(void) = default;
        virtual                     ~IResource(void) = default;
        virtual std::string         getName(void) const = 0;
        virtual float               getHeight(void) const = 0; // height pixel of image
        virtual float               getWidth(void) const = 0; // width pixel of image
        virtual short               getLife(void) const = 0;
        virtual float               getMoveSpeed(void) const = 0; // nb pixel move / update
        virtual float               getFireDeltaTime(void) const = 0; // nb sec between fire interval
        virtual IResource::Type     getType(void) const = 0;

};

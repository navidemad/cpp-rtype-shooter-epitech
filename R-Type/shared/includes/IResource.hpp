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

        struct Vec2 {
            Vec2(double x, double y) : x(x), y(y) { }
            double x, y;
        };

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
        virtual ~IResource(void) = default;
        virtual std::string                 getName(void) const = 0;
        virtual double                      getHeight(void) const = 0;
        virtual double                      getWidth(void) const = 0;
        virtual int                         getLife(void) const = 0;
        virtual double 			            getMoveSpeed(void) const = 0;
        virtual double                      getFireDeltaTime(void) const = 0;
        virtual IResource::Type             getType(void) const = 0;
        virtual IResource::Vec2             move(double deltaTime) const = 0;
        virtual IResource::Vec2             fire(double deltaTime) const = 0;

};

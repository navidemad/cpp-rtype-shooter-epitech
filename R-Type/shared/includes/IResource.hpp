#pragma once

#include <string>

class IResource {
	public:

		enum class Direction : char {
			LEFT	= 0x00,
			RIGHT	= 0x01,
			TOP		= 0x02,
			BOTTOM	= 0x03,
			UNKNOWN
		};

		enum class Type : char {
			PLAYER	= 0x00,
			BULLET	= 0x01,
			ENNEMY	= 0x02,
			BONUS	= 0x03,
	        UNKNOWN
			};
		IResource(const std::string name) : mName(name) { }
		virtual ~IResource() = default;

		virtual double 			getSpeed(void) const = 0;
		inline std::string const 	&getName() const { return mName; }

		private:
			const std::string	mName;
};

#pragma once

namespace IRessource {

	enum class Direction {
		LEFT	= 0x00,
		RIGHT	= 0x01,
		TOP		= 0x02,
		BOTTOM	= 0x03,
        UNKNOWN
	};

	enum class Type {
		PLAYER	= 0x00,
		BULLET	= 0x01,
		ENNEMY	= 0x02,
		BONUS	= 0x03,
        UNKNOWN
	};

}
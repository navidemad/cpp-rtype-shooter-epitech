#pragma once

class PlayerPacketBuilder {

	// ctor dtor
	public:
		PlayerPacketBuilder(void);
		~PlayerPacketBuilder(void);

	// move copy operators
	public:
		PlayerPacketBuilder(const PlayerPacketBuilder &) = delete;
		PlayerPacketBuilder(const PlayerPacketBuilder &&) = delete;
		const PlayerPacketBuilder &operator=(const PlayerPacketBuilder &) = delete;
		const PlayerPacketBuilder &operator=(const PlayerPacketBuilder &&) = delete;

};

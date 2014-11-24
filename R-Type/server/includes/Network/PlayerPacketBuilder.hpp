#pragma once

class PlayerPacketBuilder {

	// ctor dtor
	public:
		explicit PlayerPacketBuilder(void);
		~PlayerPacketBuilder(void);

	// move copy operators
	public:
		PlayerPacketBuilder(const PlayerPacketBuilder &) = delete;
		PlayerPacketBuilder(PlayerPacketBuilder &&) = delete;
		const PlayerPacketBuilder &operator=(const PlayerPacketBuilder &) = delete;
		const PlayerPacketBuilder &operator=(PlayerPacketBuilder &&) = delete;

};

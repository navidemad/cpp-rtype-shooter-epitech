#pragma once

class ClientPacketBuilder {

	// ctor dtor
	public:
		ClientPacketBuilder(void);
		~ClientPacketBuilder(void);

	// copy move operators
	public:
		ClientPacketBuilder(const ClientPacketBuilder &) = delete;
		ClientPacketBuilder(const ClientPacketBuilder &&) = delete;
		const ClientPacketBuilder &operator=(const ClientPacketBuilder &) = delete;
		const ClientPacketBuilder &operator=(const ClientPacketBuilder &&) = delete;

};

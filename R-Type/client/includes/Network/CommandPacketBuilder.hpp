#pragma once

class CommandPacketBuilder
{
	// ctor - dtor
	public:
		CommandPacketBuilder();
		~CommandPacketBuilder();

	// coplien form
	private:
		CommandPacketBuilder(CommandPacketBuilder const &) {}
		CommandPacketBuilder const	&operator=(CommandPacketBuilder const &) { return *this; }

};

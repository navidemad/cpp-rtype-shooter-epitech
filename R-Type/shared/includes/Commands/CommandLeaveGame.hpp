#pragma once

#include "ICommand.hpp"
#include "NoCopyable.hpp"

#include <string>

class CommandLeaveGame : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
			char	name[64];
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		explicit CommandLeaveGame(void);
		~CommandLeaveGame(void);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

};

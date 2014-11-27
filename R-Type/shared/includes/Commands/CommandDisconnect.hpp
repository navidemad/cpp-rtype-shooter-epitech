#pragma once

#include "ICommand.hpp"
#include "NoCopyable.hpp"

class CommandDisconnect : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		explicit CommandDisconnect(void);
		~CommandDisconnect(void);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

};

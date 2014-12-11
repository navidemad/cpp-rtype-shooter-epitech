#pragma once

#include "ICommand.hpp"
#include "NoCopyable.hpp"

class CommandListLevels : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandListLevels(void);
		~CommandListLevels(void);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

};

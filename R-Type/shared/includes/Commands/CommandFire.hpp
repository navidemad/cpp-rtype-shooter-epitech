#pragma once

#include "ICommand.hpp"

class CommandFire : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		explicit CommandFire(void);
		~CommandFire(void);

	// copy / move operators
	public:
		CommandFire(const CommandFire &) = delete;
		CommandFire(CommandFire &&) = delete;
		const CommandFire &operator=(const CommandFire &) = delete;
		const CommandFire &operator=(CommandFire &&) = delete;

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

};

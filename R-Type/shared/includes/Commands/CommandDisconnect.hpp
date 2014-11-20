#pragma once

#include "ICommand.hpp"

class CommandDisconnect : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandDisconnect(void);
		~CommandDisconnect(void);

	// copy / move operators
	public:
		CommandDisconnect(const CommandDisconnect &) = delete;
		CommandDisconnect(const CommandDisconnect &&) = delete;
		const CommandDisconnect &operator=(const CommandDisconnect &) = delete;
		const CommandDisconnect &operator=(const CommandDisconnect &&) = delete;

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

};

#pragma once

#include <string>
#include "ICommand.hpp"

class CommandLeaveGame : public ICommand {

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

	// copy / move operators
	public:
		CommandLeaveGame(const CommandLeaveGame &) = delete;
		CommandLeaveGame(CommandLeaveGame &&) = delete;
		const CommandLeaveGame &operator=(const CommandLeaveGame &) = delete;
		const CommandLeaveGame &operator=(CommandLeaveGame &&) = delete;

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

};

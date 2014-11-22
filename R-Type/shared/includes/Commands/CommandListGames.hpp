#pragma once

#include "ICommand.hpp"

class CommandListGames : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		explicit CommandListGames(void);
		~CommandListGames(void);

	// copy / move operators
	public:
		CommandListGames(const CommandListGames &) = delete;
		CommandListGames(CommandListGames &&) = delete;
		const CommandListGames &operator=(const CommandListGames &) = delete;
		const CommandListGames &operator=(CommandListGames &&) = delete;

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

};

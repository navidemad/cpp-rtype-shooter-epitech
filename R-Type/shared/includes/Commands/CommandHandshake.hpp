#pragma once

#include "ICommand.hpp"

class CommandHandshake : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
		};
		#pragma pack(pop)

		#pragma pack(push, 1)
		struct PacketFromClient {
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandHandshake(void);
		~CommandHandshake(void);

	// copy / move operators
	public:
		CommandHandshake(const CommandHandshake &) = delete;
		CommandHandshake(const CommandHandshake &&) = delete;
		const CommandHandshake &operator=(const CommandHandshake &) = delete;
		const CommandHandshake &operator=(const CommandHandshake &&) = delete;

	// public pure methods
	public:
		ICommand::Instruction		getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int						getSizeToRead(void) const;
		void										initFromMessage(const IClientSocket::Message &message);

};

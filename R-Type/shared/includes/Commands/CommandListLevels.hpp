#pragma once

#include "ICommand.hpp"

class CommandListLevels : public ICommand {

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

	// copy / move operators
	public:
		CommandListLevels(const CommandListLevels &) = delete;
		CommandListLevels(const CommandListLevels &&) = delete;
		const CommandListLevels &operator=(const CommandListLevels &) = delete;
		const CommandListLevels &operator=(const CommandListLevels &&) = delete;

	// public pure methods
	public:
		ICommand::Instruction		getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int						getSizeToRead(void) const;
		void										initFromMessage(const IClientSocket::Message &message);

};

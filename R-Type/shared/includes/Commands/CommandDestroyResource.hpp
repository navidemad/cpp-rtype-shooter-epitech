#pragma once

#include "ICommand.hpp"

class CommandDestroyResource : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			int32_t	id;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandDestroyResource(void);
		~CommandDestroyResource(void);

	// copy / move operators
	public:
		CommandDestroyResource(const CommandDestroyResource &) = delete;
		CommandDestroyResource(const CommandDestroyResource &&) = delete;
		const CommandDestroyResource &operator=(const CommandDestroyResource &) = delete;
		const CommandDestroyResource &operator=(const CommandDestroyResource &&) = delete;

	// getter - setters
	public:
		int 	getId(void) const;
		void	setId(int id);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		int mId;

};

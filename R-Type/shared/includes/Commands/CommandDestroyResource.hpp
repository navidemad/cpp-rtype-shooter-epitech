#pragma once

#include "ICommand.hpp"
#include "NoCopyable.hpp"

class CommandDestroyResource : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			uint64_t id;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandDestroyResource(void);
		~CommandDestroyResource(void);

	// getter - setters
	public:
		uint64_t 	getId(void) const;
		void		setId(uint64_t id);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		uint64_t mId;

};

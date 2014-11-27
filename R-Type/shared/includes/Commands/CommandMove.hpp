#pragma once

#include "IResource.hpp"
#include "ICommand.hpp"
#include "NoCopyable.hpp"

class CommandMove : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
			char direction;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		explicit CommandMove(void);
		~CommandMove(void);

	// getter - setters
	public:
		IResource::Direction getDirection(void) const;
		void setDirection(IResource::Direction direction);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		IResource::Direction mDirection;

};

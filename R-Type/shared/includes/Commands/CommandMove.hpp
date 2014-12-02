#pragma once

#include "IRessource.hpp"
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
		IRessource::Direction getDirection(void) const;
		void setDirection(IRessource::Direction direction);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		IRessource::Direction mDirection;

};

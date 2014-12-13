#pragma once

#include "ICommand.hpp"
#include "NoCopyable.hpp"

class CommandTimeElapsedPing : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			double timeElapsed;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandTimeElapsedPing(void);
		~CommandTimeElapsedPing(void);

	// getter - setters
	public:
		double		getTimeElapsed(void) const;
		void		setTimeElapsed(double timeElapsed);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		double mTimeElapsed;

};

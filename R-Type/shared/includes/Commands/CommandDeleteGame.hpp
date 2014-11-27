#pragma once

#include "ICommand.hpp"
#include "NoCopyable.hpp"

#include <string>

class CommandDeleteGame : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
			char	name[64];
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		explicit CommandDeleteGame(void);
		~CommandDeleteGame(void);

	// getter - setters
	public:
		const std::string &getName(void) const;
		void setName(const std::string &name);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		std::string	mName;

};

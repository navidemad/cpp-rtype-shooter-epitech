#pragma once

#include "ICommand.hpp"
#include "NoCopyable.hpp"

#include <string>

class CommandUpdatePseudo : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
			char	pseudo[64];
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandUpdatePseudo(void);
		~CommandUpdatePseudo(void);

	// getter - setters
	public:
		const std::string &getPseudo(void) const;
		void setPseudo(const std::string &pseudo);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		std::string mPseudo;

};

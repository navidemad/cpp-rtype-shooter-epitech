#pragma once

#include <string>
#include "ICommand.hpp"

class CommandUpdatePseudo : public ICommand {

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

	// copy / move operators
	public:
		CommandUpdatePseudo(const CommandUpdatePseudo &) = delete;
		CommandUpdatePseudo(const CommandUpdatePseudo &&) = delete;
		const CommandUpdatePseudo &operator=(const CommandUpdatePseudo &) = delete;
		const CommandUpdatePseudo &operator=(const CommandUpdatePseudo &&) = delete;

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

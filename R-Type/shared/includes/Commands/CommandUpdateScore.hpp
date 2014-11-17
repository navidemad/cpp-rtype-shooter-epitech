#pragma once

#include <string>
#include "ICommand.hpp"

class CommandUpdateScore : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			int32_t	id;
			char		pseudo[64];
			int32_t score;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandUpdateScore(void);
		~CommandUpdateScore(void);

	// copy / move operators
	public:
		CommandUpdateScore(const CommandUpdateScore &) = delete;
		CommandUpdateScore(const CommandUpdateScore &&) = delete;
		const CommandUpdateScore &operator=(const CommandUpdateScore &) = delete;
		const CommandUpdateScore &operator=(const CommandUpdateScore &&) = delete;

	// getter - setters
	public:
		int getId(void) const;
		const std::string &getPseudo(void) const;
		int getScore(void) const;

		void setId(int id);
		void setPseudo(const std::string &pseudo);
		void setScore(int score);

	// public pure methods
	public:
		ICommand::Instruction		getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int						getSizeToRead(void) const;
		void										initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		int 					mId;
		std::string 	mPseudo;
		int 					mScore;

};

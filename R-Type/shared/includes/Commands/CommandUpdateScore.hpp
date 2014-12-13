#pragma once

#include "ICommand.hpp"
#include "NoCopyable.hpp"

#include <string>

class CommandUpdateScore : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			uint64_t	id;
			char	pseudo[64];
			uint64_t score;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandUpdateScore(void);
		~CommandUpdateScore(void);

	// getter - setters
	public:
		uint64_t getId(void) const;
		const std::string &getPseudo(void) const;
		uint64_t getScore(void) const;

		void setId(uint64_t id);
		void setPseudo(const std::string &pseudo);
		void setScore(uint64_t score);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		uint64_t 		mId;
		std::string		mPseudo;
		uint64_t 		mScore;

};

#pragma once

#include <string>
#include "ICommand.hpp"

class CommandShowLevel : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			char		name[64]
			int32_t	scriptSize;
			char		script[4096];
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandShowLevel(void);
		~CommandShowLevel(void);

	// copy / move operators
	public:
		CommandShowLevel(const CommandShowLevel &) = delete;
		CommandShowLevel(const CommandShowLevel &&) = delete;
		const CommandShowLevel &operator=(const CommandShowLevel &) = delete;
		const CommandShowLevel &operator=(const CommandShowLevel &&) = delete;

	// getter - setters
	public:
		const std::string &getName(void) const;
		const std::string &getScript(void) const;

		void setName(const std::string &name);
		void setScript(const std::string &script);

	// public pure methods
	public:
		ICommand::Instruction		getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int						getSizeToRead(void) const;
		void										initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		std::string mName;
		std::string mScript;

};

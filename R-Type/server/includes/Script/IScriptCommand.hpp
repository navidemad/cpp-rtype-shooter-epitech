#pragma once

class IScriptCommand {
	// virtual destructor
	public:
		virtual ~IScriptCommand(void) {}

	// Instructions
	public:
	enum class Instruction {
		NAME = 0,
		REQUIRE,
		ACTION,
		ADD_CRON,
		REMOVE_CRON,
		UNKNOWN
	};

	// public pure methods
	public:
	virtual IScriptCommand::Instruction	getInstruction(void) const = 0;
};
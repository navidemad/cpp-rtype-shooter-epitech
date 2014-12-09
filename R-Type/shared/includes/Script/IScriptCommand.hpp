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
		REMOVE_CRON
	};

	enum class cmdAction {
		NAME = 0,
		FRAME,
		IDCRON,
		IDMONSTER,
		X,
		Y,
		ANGLE,
		TIMER,
		SPAWNMOBAT,
		MOVEMOBTO
	};

	// public pure methods
	public:
	virtual IScriptCommand::Instruction	getInstruction(void) const = 0;
	virtual double						getFrame(void) const = 0;
};
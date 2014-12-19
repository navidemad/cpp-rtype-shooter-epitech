#pragma once

#include <string>

class AScriptCommand {
	public:
		enum class Instruction : char { NAME = 0, REQUIRE, SPAWN };
		AScriptCommand(double frame, AScriptCommand::Instruction instruction) : mFrame(frame), mInstruction(instruction) { }
		inline double getFrame(void) const { return mFrame; }
		inline AScriptCommand::Instruction	getInstruction(void) const { return mInstruction; }
	protected:
		double mFrame;
		AScriptCommand::Instruction mInstruction;
};

class ScriptRequire : public AScriptCommand {
	public:
		ScriptRequire(double frame) : AScriptCommand(frame, AScriptCommand::Instruction::REQUIRE) { }
		inline const std::string& getRessourceName(void) const { return mRessourceName; }
		inline void setRessourceName(const std::string& ressourceName) { mRessourceName = ressourceName; }
	private:
		std::string mRessourceName;
};

class ScriptName : public AScriptCommand {
	public:
		ScriptName(double frame) : AScriptCommand(frame, AScriptCommand::Instruction::NAME) { }
		inline const std::string& getStageName(void) const { return mStageName; }
		inline void setStageName(const std::string& stageName) { mStageName = stageName; }
	private:
		std::string mStageName;
};

class ScriptSpawn : public AScriptCommand {
	public:
		ScriptSpawn(double frame) : AScriptCommand(frame, AScriptCommand::Instruction::SPAWN) { }
		const std::string& getSpawnName(void) const { return mSpawnName; }
		void setSpawnName(const std::string& spawnName) { mSpawnName = spawnName; }
		inline double getX(void) const { return mX; }
		inline double getY(void) const { return mY; }
		inline double getAngle(void) const { return mAngle; }
		inline void setX(double x) { mX = x; }
		inline void setY(double y) { mY = y; }
		inline void setAngle(double angle) { mAngle = angle; }
	
	private:
		std::string mSpawnName;
		double mX, mY, mAngle;
};

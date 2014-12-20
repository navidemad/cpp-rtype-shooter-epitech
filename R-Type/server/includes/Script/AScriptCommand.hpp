#pragma once

#include <string>

class AScriptCommand {
	public:
		enum class Instruction : char { NAME = 0, REQUIRE, SPAWN };
		AScriptCommand(double frame, AScriptCommand::Instruction instruction) : mFrame(frame), mInstruction(instruction) { }
        virtual ~AScriptCommand() = default;
		double getFrame(void) const { return mFrame; }
		AScriptCommand::Instruction	getInstruction(void) const { return mInstruction; }
	protected:
		double mFrame;
		AScriptCommand::Instruction mInstruction;
};

class ScriptRequire : public AScriptCommand {
	public:
		ScriptRequire(double frame) : AScriptCommand(frame, AScriptCommand::Instruction::REQUIRE) { }
        virtual ~ScriptRequire() = default;
		inline const std::string& getRessourceName(void) const { return mRessourceName; }
		void setRessourceName(const std::string& ressourceName) { mRessourceName = ressourceName; }
	private:
		std::string mRessourceName;
};

class ScriptName : public AScriptCommand {
	public:
		ScriptName(double frame) : AScriptCommand(frame, AScriptCommand::Instruction::NAME) { }
        virtual ~ScriptName() = default;
		inline const std::string& getStageName(void) const { return mStageName; }
		inline void setStageName(const std::string& stageName) { mStageName = stageName; }
	private:
		std::string mStageName;
};

class ScriptSpawn : public AScriptCommand {
	public:
		ScriptSpawn(double frame) : AScriptCommand(frame, AScriptCommand::Instruction::SPAWN) { }
        virtual ~ScriptSpawn() = default;
		const std::string& getSpawnName(void) const { return mSpawnName; }
		void setSpawnName(const std::string& spawnName) { mSpawnName = spawnName; }
		double getX(void) const { return mX; }
		double getY(void) const { return mY; }
		double getAngle(void) const { return mAngle; }
		void setX(double x) { mX = x; }
		void setY(double y) { mY = y; }
		void setAngle(double angle) { mAngle = angle; }
	
	private:
		std::string mSpawnName;
		double mX, mY, mAngle;
};

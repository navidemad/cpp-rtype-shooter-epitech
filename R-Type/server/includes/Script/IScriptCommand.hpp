#pragma once

#include <string>
#include <iostream>

class IScriptCommand {
	public:
		enum class Instruction : char { NAME = 0, REQUIRE, SPAWN };
	public:
        virtual ~IScriptCommand() = default;
    public:
        virtual IScriptCommand* clone(void) const = 0;
        virtual float getFrame(void) const = 0;
        virtual void setFrame(float) = 0;
        virtual IScriptCommand::Instruction getInstruction(void) const = 0;
        virtual void setInstruction(IScriptCommand::Instruction) = 0;
};

class ScriptSpawn : public IScriptCommand {
    public:
        virtual IScriptCommand* clone(void) const { return new ScriptSpawn(*this); }
        virtual float getFrame(void) const { return mFrame; }
        virtual void setFrame(float frame) { mFrame = frame; }
        virtual IScriptCommand::Instruction getInstruction(void) const { return mInstruction; }
        virtual void setInstruction(IScriptCommand::Instruction instruction) { mInstruction = instruction; }
    public:
        ScriptSpawn() = default;
        ~ScriptSpawn() = default;
        ScriptSpawn(const ScriptSpawn& rhs) :
            mFrame(rhs.getFrame()),
            mInstruction(rhs.getInstruction()),
            mSpawnName(rhs.getSpawnName()),
            mX(rhs.getX()),
            mY(rhs.getY()),
            mAngle(rhs.getAngle()) { }
        const ScriptSpawn& operator=(const ScriptSpawn& rhs) {
            if (this != &rhs) {
                mFrame = rhs.getFrame();
                mInstruction = rhs.getInstruction();
                mSpawnName = rhs.getSpawnName();
                mX = rhs.getX();
                mY = rhs.getY();
                mAngle = rhs.getAngle();
            }
            return *this;
        }
    public:
        const std::string& getSpawnName(void) const { return mSpawnName; }
        void setSpawnName(const std::string& spawnName) { mSpawnName = spawnName; }
        float getX(void) const { return mX; }
        void setX(float x) { mX = x; }
        float getY(void) const { return mY; }
        void setY(float y) { mY = y; }
        float getAngle(void) const { return mAngle; }
        void setAngle(float angle) { mAngle = angle; }
    private:
        float mFrame;
        IScriptCommand::Instruction mInstruction;
    private:
        std::string mSpawnName;
        float mX;
        float mY;
        float mAngle;
};

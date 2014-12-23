#pragma once

#include <string>
#include <iostream>

class IScriptCommand {
	public:
		enum class Instruction : char { NAME = 0, REQUIRE, SPAWN };
	public:
        virtual ~IScriptCommand() = default;
    public:
        virtual double getFrame(void) const = 0;
        virtual void setFrame(double) = 0;
        virtual IScriptCommand::Instruction getInstruction(void) const = 0;
        virtual void setInstruction(IScriptCommand::Instruction) = 0;
};

class ScriptRequire : public IScriptCommand {
    public:
        virtual double getFrame(void) const { return mFrame; }
        virtual void setFrame(double frame) { mFrame = frame; }
        virtual IScriptCommand::Instruction getInstruction(void) const { return mInstruction; }
        virtual void setInstruction(IScriptCommand::Instruction instruction) { mInstruction = instruction; }
    public:
        explicit ScriptRequire() = default;
        virtual ~ScriptRequire() = default;
        ScriptRequire(const ScriptRequire& rhs) :
            mFrame(rhs.getFrame()),
            mInstruction(rhs.getInstruction()),
            mResourceName(rhs.getResourceName()) { }
        ScriptRequire& operator=(const ScriptRequire& rhs) {
            if (this != &rhs) {
                mFrame = rhs.getFrame();
                mInstruction = rhs.getInstruction();
                mResourceName = rhs.getResourceName();
            }
            return *this;
        }
    public:
        const std::string& getResourceName(void) const { return mResourceName; }
        void setResourceName(const std::string& ressourceName) { mResourceName = ressourceName; }
    private:
        double mFrame;
        IScriptCommand::Instruction mInstruction;
    private:
        std::string mResourceName;
};

class ScriptName : public IScriptCommand {
    public:
        virtual double getFrame(void) const { return mFrame; }
        virtual void setFrame(double frame) { mFrame = frame; }
        virtual IScriptCommand::Instruction getInstruction(void) const { return mInstruction; }
        virtual void setInstruction(IScriptCommand::Instruction instruction) { mInstruction = instruction; }
    public:
        explicit ScriptName() = default;
        virtual ~ScriptName() = default;
        ScriptName(const ScriptName& rhs) :
            mFrame(rhs.getFrame()),
            mInstruction(rhs.getInstruction()),
            mStageName(rhs.getStageName()) { }
        ScriptName& operator=(const ScriptName& rhs) {
            if (this != &rhs) {
                mFrame = rhs.getFrame();
                mInstruction = rhs.getInstruction();
                mStageName = rhs.getStageName();
            }
            return *this;
        }
    public:
        const std::string& getStageName(void) const { return mStageName; }
        void setStageName(const std::string& stageName) { mStageName = stageName; }
    private:
        double mFrame;
        IScriptCommand::Instruction mInstruction;
    private:
        std::string mStageName;
};

class ScriptSpawn : public IScriptCommand {
    public:
        virtual double getFrame(void) const { return mFrame; }
        virtual void setFrame(double frame) { mFrame = frame; }
        virtual IScriptCommand::Instruction getInstruction(void) const { return mInstruction; }
        virtual void setInstruction(IScriptCommand::Instruction instruction) { mInstruction = instruction; }
    public:
        explicit ScriptSpawn() = default;
        virtual ~ScriptSpawn() = default;
        ScriptSpawn(const ScriptSpawn& rhs) :
            mFrame(rhs.getFrame()),
            mInstruction(rhs.getInstruction()),
            mSpawnName(rhs.getSpawnName()),
            mX(rhs.getX()),
            mY(rhs.getY()),
            mAngle(rhs.getAngle()) { }
        ScriptSpawn& operator=(const ScriptSpawn& rhs) {
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
        double getX(void) const { return mX; }
        void setX(double x) { mX = x; }
        double getY(void) const { return mY; }
        void setY(double y) { mY = y; }
        double getAngle(void) const { return mAngle; }
        void setAngle(double angle) { mAngle = angle; }
    private:
        double mFrame;
        IScriptCommand::Instruction mInstruction;
    private:
        std::string mSpawnName;
        double mX;
        double mY;
        double mAngle;
};

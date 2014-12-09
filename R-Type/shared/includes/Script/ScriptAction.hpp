#pragma once

#include <string>
#include "IScriptCommand.hpp"

class ScriptAction : public IScriptCommand {
	// virtual destructor
	public:
		explicit ScriptAction(void) { }
		~ScriptAction(void) { }

	// public pure methods
	public:
		IScriptCommand::Instruction	getInstruction(void) const { return IScriptCommand::Instruction::ACTION; }
		virtual double						getFrame(void) const { return mActionFrame; }
	// actions enum
	public:
		enum class TYPE { SPAWN_MOB, MOVE_MOB };

	// interface action class
	public:
		class IActionType {
			public:
				virtual ~IActionType(void) {}
		};

	// getter-setter
	public:
		double							getActionFrame(void) const { return mActionFrame; }
		const std::string&				getActionMobAction(void) const { return mActionMobAction; }
		ScriptAction::TYPE				getActionType(void) const { return mType; }
		std::shared_ptr<IActionType>	getActionParams(void) const { return mParams; }

		void							setActionFrame(double frame) { mActionFrame = frame; }
		void							setActionMobAction(const std::string& mobAction) { mActionMobAction = mobAction; }
		void							setActionType(ScriptAction::TYPE type) { mType = type; }
		void							setActionParams(std::shared_ptr<IActionType> params) { mParams = params; }

	// actions class
	public:
		class SpawnMob : public IActionType {

			// ctor / dtor
			public:
				SpawnMob(void) { }
				~SpawnMob(void) { }

			// getter-setter
			public:
				int						getActionIdMonster(void) const { return mIdMonster; }
				std::string				getActionName(void) const { return mName; }
				int						getActionXpos(void) const { return mXpos; }
				int						getActionYpos(void) const { return mYpos; }
				int						getActionAngle(void) const { return mAngle; }

				void					setActionIdMonster(const int& idMonster) { mIdMonster = idMonster; }
				void					setActionName(const std::string& name) { mName = name; }
				void					setActionXpos(const int& xPos) { mXpos = xPos; }
				void					setActionYpos(const int& yPos) { mYpos = yPos; }
				void					setActionAngle(const int& angle) { mAngle = angle; }

			// attributes
			public:
				int mIdMonster;
				std::string mName;
				int mXpos;
				int mYpos;
				int mAngle;
		};

		class MoveMob : public IActionType {

			// ctor / dtor
			public:
				MoveMob(void) { }
				~MoveMob(void) { }

			// getter-setter
			public:
				int						getActionIdMonster(void) const { return mIdMonster; }
				int						getActionAngle(void) const { return mAngle; }

				void					setActionIdMonster(const int& idMonster) { mIdMonster = idMonster; }
				void					setActionAngle(const int& angle) { mAngle = angle; }

			// attributes
			public:
				int						mIdMonster;
				int						mAngle;
		};

	// attribut
	public:
		double							mActionFrame;
		std::string						mActionMobAction;
		std::shared_ptr<IActionType>	mParams;
		ScriptAction::TYPE				mType;
};
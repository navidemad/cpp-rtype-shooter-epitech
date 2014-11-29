#pragma once

#include <string>
#include "IScriptCommand.hpp"

class ScriptAction : public IScriptCommand {
	// virtual destructor
	public:
		explicit ScriptAction(void);
		~ScriptAction(void);

	// public pure methods
	public:
		IScriptCommand::Instruction	getInstruction(void) const { return IScriptCommand::Instruction::ACTION; }

	// getter-setter
	public:
		int						getActionFrame(void) const { return mActionFrame; }
		std::string				getActionMobAction(void) const;
		int						getActionSpawnIdMonster(void) const;
		std::string				getActionSpawnName(void) const;
		int						getActionSpawnXpos(void) const;
		int						getActionSpawnYpos(void) const;
		int						getActionSpawnAngle(void) const;
		int						getActionMoveMobIdMonster(void) const;
		int						getActionMoveMobAngle(void) const;

		void					setActionFrame(const int& frame) { mActionFrame = frame; }
		void					setActionMobAction(const std::string& mobAction) { mActionMobAction = mobAction; }
		void					setActionSpawnIdMonster(const int& idMonster) { mSpawnIdMonster = idMonster; }
		void					setActionSpawnName(const std::string& name) { mSpawnName = name; }
		void					setActionSpawnXpos(const int& xPos) { mSpawnXpos = xPos; }
		void					setActionSpawnYpos(const int& yPos) { mSpawnYpos = yPos; }
		void					setActionMoveMobIdMonster(const int& idMonster) { mMoveMobIdMonster = idMonster; }
		void					setActionMoveMobAngle(const int& angle) { mMoveMobAngle = angle; }

	// attribut
	public:
		int						mActionFrame;
		std::string				mActionMobAction;
		int						mSpawnIdMonster;
		std::string				mSpawnName;
		int						mSpawnXpos;
		int						mSpawnYpos;
		int						mSpawnAngle;
		int						mMoveMobIdMonster;
		int						mMoveMobAngle;
};
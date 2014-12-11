#pragma once

#include <string>
#include "IScriptCommand.hpp"

class ScriptAction : public IScriptCommand {
	// virtual destructor
	public:
		ScriptAction(void) = default;
		~ScriptAction(void) = default;

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
				double					getActionXpos(void) const { return mXpos; }
				double					getActionYpos(void) const { return mYpos; }
				double					getActionAngle(void) const { return mAngle; }

				void					setActionIdMonster(int idMonster) { mIdMonster = idMonster; }
				void					setActionName(const std::string& name) { mName = name; }
				void					setActionXpos(double xPos) { mXpos = xPos; }
				void					setActionYpos(double yPos) { mYpos = yPos; }
				void					setActionAngle(double angle) { mAngle = angle; }

			// attributes
			public:
				int mIdMonster;
				std::string mName;
				double mXpos;
				double mYpos;
				double mAngle;

            // overload << display
            public:
                friend std::ostream&                operator << (std::ostream& os, std::shared_ptr<SpawnMob> rhs) {
                    os << "  [ SpawnMob ]" << std::endl <<
                        "    * mIdMonster: '" << rhs->getActionIdMonster() << std::endl <<
                        "    * mName: '" << rhs->getActionName() << std::endl <<
                        "    * mXpos: '" << rhs->getActionXpos() << std::endl <<
                        "    * mYpos: '" << rhs->getActionYpos() << std::endl <<
                        "    * mAngle: '" << rhs->getActionAngle() << std::endl;
                    return os;
                }
		};

		class MoveMob : public IActionType {

			// ctor / dtor
			public:
				MoveMob(void) { }
				~MoveMob(void) { }

			// getter-setter
			public:
				int						getActionIdMonster(void) const { return mIdMonster; }
				double					getActionAngle(void) const { return mAngle; }

				void					setActionIdMonster(int idMonster) { mIdMonster = idMonster; }
				void					setActionAngle(double angle) { mAngle = angle; }

			// attributes
			public:
				int						mIdMonster;
				double					mAngle;

            // overload << display
            public:
                friend std::ostream&                operator << (std::ostream& os, std::shared_ptr<MoveMob> rhs) {
                    os << "  [ MoveMob ]" << std::endl <<
                        "    * mIdMonster: '" << rhs->getActionIdMonster() << std::endl <<
                        "    * mAngle: '" << rhs->getActionAngle() << std::endl;
                    return os;
                }
		};

	// attribut
	public:
		double							mActionFrame;
		std::string						mActionMobAction;
		std::shared_ptr<IActionType>	mParams;
		ScriptAction::TYPE				mType;

    // overload << display
    public:
        friend std::ostream&                operator << (std::ostream& os, std::shared_ptr<ScriptAction> rhs) {
            os <<
                "[ScriptAction] [Frame #" << rhs->getFrame() << "]" << std::endl <<
                "  - mActionFrame: '" << rhs->getActionFrame() << std::endl <<
                "  - mActionMobAction: '" << rhs->getActionMobAction() << std::endl <<
                "  - mParams: '" << rhs->getActionParams() << std::endl;
            return os;
        }
};
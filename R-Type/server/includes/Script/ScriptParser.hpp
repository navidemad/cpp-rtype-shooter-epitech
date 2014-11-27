#pragma once

#include <list>
#include "Utils.hpp"
#include "NoCopyable.hpp"

class ScriptParser : public NoCopyable {
	// ctor / dtor
	public:
		explicit ScriptParser(void);
		~ScriptParser(void);

	// copy / move operators
	public:
		ScriptParser(const ScriptParser &) = delete;
		ScriptParser(const ScriptParser &&) = delete;
		const ScriptParser &operator=(const ScriptParser &) = delete;
		const ScriptParser &operator=(const ScriptParser &&) = delete;

	// internal functions
	public:
		void			getName(const std::string&);
		void			getActions(const std::string&);
		void			parseFile(std::ifstream &);
		void			cmdName(const std::string&);
		void			cmdRequire(const std::string&);
		void			cmdAction(const std::string&);
		void			cmdAddCron(const std::string&);
		void			cmdRemoveCron(const std::string&);
		void			jumpToNextToken(void);
		void			setStringToParse(const std::string &str);
		void			setTokenSep(char tokenSep);
		std::string		extractWord(void);

		template <typename T>
		T		extractValue(void){
			T		val;

			if (this->_wtab.size() == 0)
				return 0;
			val = Utils::getNbr<T>(this->_wtab.front());
			this->jumpToNextToken();
			return val;
		}

	private:
		char					_tokenSep;
		std::string				_str;
		std::list<std::string>	_wtab;

	private:
		void						splitString(void);

	};

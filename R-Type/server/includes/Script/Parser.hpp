#pragma once

#include <string>
#include <list>
#include "NoCopyable.hpp"

class Parser : public NoCopyable {

    // ctor / dtor
    public:
        explicit Parser(void);
        ~Parser(void);

	public:
		std::string extractWord();
		void		jumpToNextToken(void);
		void		setStringToParse(const std::string &str);
		void		setTokenSep(char);
		void		splitString(void);

		template <typename T>
		T		extractValue(void){
			T		val;

			if (this->mWtab.size() == 0)
				return 0;
			val = Utils::getNbr<T>(this->mWtab.front());
			this->jumpToNextToken();
			return val;
		}

	private:
		char					mTokenSep;
		std::string				mStr;
		std::list<std::string>	mWtab;
};

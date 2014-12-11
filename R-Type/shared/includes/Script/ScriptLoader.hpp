#pragma once

#include "NoCopyable.hpp"
#include "Script.hpp"
#include "IReaddir.hpp"

#include <sstream>
#include <string>
#include <map>
#include <memory>

class ScriptLoader : public NoCopyable {

	// ctor / dtor
public:
	ScriptLoader(void);
	~ScriptLoader(void);

	// internal functions
public:
	bool isExist(const std::string& stage_name) const;
	const Script& getScript(const std::string& stage_name) const;
	void loadAll(void);
    const std::map<std::string, Script>& getScripts() const;

	// attributes
private:
	std::map<std::string, Script> mScripts;
	std::shared_ptr<IReaddir> mReaddir;
};

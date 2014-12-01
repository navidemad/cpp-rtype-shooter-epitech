#pragma once

#include <sstream>
#include "NoCopyable.hpp"
#include <string>
#include "Script.hpp"
#include <map>
#include <memory>

class ScriptLoader : public NoCopyable {

	// ctor / dtor
public:
	explicit ScriptLoader(void);
	~ScriptLoader(void);

	// internal functions
public:
	std::shared_ptr<Script> loadScript(const std::string& stage_name);
	void loadAll(void);

	// attributes
private:
	std::map<std::string, std::shared_ptr<Script>> mScripts;
};

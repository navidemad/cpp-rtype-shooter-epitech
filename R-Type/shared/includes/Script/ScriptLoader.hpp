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
	explicit ScriptLoader(void);
	~ScriptLoader(void);

	// internal functions
public:
	std::shared_ptr<Script> loadScript(const std::string& stage_name);
	void loadAll(void);
    const std::map<std::string, std::shared_ptr<Script>>& getScripts() const;

	// attributes
private:
	std::map<std::string, std::shared_ptr<Script>> mScripts;
	std::shared_ptr<IReaddir> mReaddir;
};
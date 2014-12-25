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

    //utils
public:
    void logInfo(const std::string &log) const;

	// internal functions
public:
	bool has(const std::string& stage_name) const;
    const std::shared_ptr<NGame::Script>& get(const std::string& stage_name) const;
	bool loadAll(void);
    const std::map<std::string, std::shared_ptr<NGame::Script>>& getScripts() const;

	// attributes
private:
    std::map<std::string, std::shared_ptr<NGame::Script>> mScripts;
	std::shared_ptr<IReaddir> mReaddir;
};

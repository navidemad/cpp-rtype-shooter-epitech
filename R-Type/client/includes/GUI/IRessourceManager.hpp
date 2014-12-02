#pragma once

template<typename T>
class IRessourceManager
{
	public:
		virtual ~IRessourceManager() {}

	// virtual methods
	public:
		virtual void	loadResources() = 0;
		virtual void	unloadResources() = 0;
		virtual T 		&getResource(std::string const &key) = 0;
};

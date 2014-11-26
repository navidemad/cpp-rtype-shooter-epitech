#pragma once

template<typename T>
class IResourceManager
{
	public:
		virtual ~IResourceManager() {}

	// virtual methods
	public:
		virtual void	loadResources() = 0;
		virtual void	unloadResources() = 0;
		virtual T 		&getResource(std::string const &key) = 0;
};

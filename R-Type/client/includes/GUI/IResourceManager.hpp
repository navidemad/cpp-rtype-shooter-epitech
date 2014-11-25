#pragma once

template<typename T>
class IResourceManager
{
	public:
		virtual ~IResourceManager() {}

	// virtual methods
	public:
		virtual void		loadResources() = 0;
		virtual void		unloadResources() = 0;
		virtual T const		&getResource(std::string const &key) const = 0;
};

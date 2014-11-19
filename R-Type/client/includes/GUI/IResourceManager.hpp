#pragma once

template<class T>
class IResourceManager
{
	public:
		virtual ~IResourceManager() {}

	// virtual methods
	public:
		virtual void		loadResource() = 0;
		virtual void		unloadResource() = 0;
		virtual T const		&getResource() = 0;
};

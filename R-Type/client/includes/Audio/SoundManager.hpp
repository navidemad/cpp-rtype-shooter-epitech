#pragma once

class SoundManager
{
	// ctor - dtor
	public:
		SoundManager();
		~SoundManager();

	// coplien form
	private:
		SoundManager(SoundManager const &) {}
		SoundManager const	&operator=(SoundManager const &) { return *this; }
};

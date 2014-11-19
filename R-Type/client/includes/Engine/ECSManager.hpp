#pragma once

class ECSManager
{
	// ctor - dtor
	public:
		ECSManager();
		~ECSManager();

	// coplien form
	private:
		ECSManager(ECSManager const &);
		ECSManager const	&operator=(ECSManager const &);
};

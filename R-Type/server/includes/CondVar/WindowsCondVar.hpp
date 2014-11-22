#pragma once

#include "IMutex.hpp"
#include "ICondVar.hpp"
#include "CondVarException.hpp"

# include <WinSock2.h>

# define _CONDITION_EVENT_ONE 0
# define _CONDITION_EVENT_ALL 1

class WindowsCondVar : public ICondVar {

	// ctor dtor
	public:
		explicit WindowsCondVar(void);
		~WindowsCondVar(void);

	// copy / move operators
	public:
		WindowsCondVar(const WindowsCondVar &) = delete;
		WindowsCondVar(WindowsCondVar &&) = delete;
		const WindowsCondVar &operator=(const WindowsCondVar &) = delete;
		const WindowsCondVar &operator=(WindowsCondVar &&) = delete;

	// interface implementation
	public:
        void wait(std::shared_ptr<IMutex>);
		void notifyOne(void);
		void notifyAll(void);

    // attributes
    private:
    	void _wait();
        HANDLE mEvents[2];
    	unsigned int mWaitersCount;
    	CRITICAL_SECTION mWaitersCountLock;
};

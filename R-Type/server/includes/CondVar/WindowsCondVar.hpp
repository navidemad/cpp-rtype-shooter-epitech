#pragma once

#include "IMutex.hpp"
#include "ICondVar.hpp"
#include "NoCopyable.hpp"

class WindowsCondVar : public NoCopyable, public ICondVar {

    // enum events
    public:
        enum Event {
            SIGNAL = 0,
            BROADCAST = 1,
            MAX_EVENTS = 2
        };

	// ctor dtor
	public:
		WindowsCondVar(void);
		~WindowsCondVar(void);

	// interface implementation
	public:
        void wait(std::shared_ptr<IMutex>);
		void notifyOne(void);
		void notifyAll(void);

    // attributes
    private:
        HANDLE                      mEvents[WindowsCondVar::Event::MAX_EVENTS];
    	unsigned int                mWaitersCount;
    	std::shared_ptr<IMutex>     mWaitersCountLock;
};

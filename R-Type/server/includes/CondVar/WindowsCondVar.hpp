#pragma once

#include "IMutex.hpp"
#include "ICondVar.hpp"

class WindowsCondVar : public ICondVar {

    // enum events
    public:
        enum Event {
            SIGNAL = 0,
            BROADCAST = 1,
            MAX_EVENTS = 2
        };

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
        HANDLE                      mEvents[WindowsCondVar::Event::MAX_EVENTS];
    	unsigned int                mWaitersCount;
    	std::shared_ptr<IMutex>     mWaitersCountLock;
};

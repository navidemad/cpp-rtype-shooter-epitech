#pragma once

#include "IThread.hpp"
# include <WinSock2.h>
#include "ThreadException.hpp"

template <typename U, typename T>
class WindowsThread : public IThread<U, T> {

	// ctor dtor
	public:
		WindowsThread(void) {}
		~WindowsThread(void) {
            cancel();
		}

	// copy / move operators
	public:
		WindowsThread(const WindowsThread &) = delete;
		WindowsThread(const WindowsThread &&) = delete;
		const WindowsThread &operator=(const WindowsThread &) = delete;
		const WindowsThread &operator=(const WindowsThread &&) = delete;

	// enum ret value
	public:

	// interface implementation
	public:
		void create(U callObj, T fctParam) {
			mCallObj  = callObj;
			mFctParam = fctParam;

            mThread = CreateThread(
                NULL, 
                0, 
                reinterpret_cast<LPTHREAD_START_ROUTINE>(start_thread_trampoline<U, T>),
                reinterpret_cast<LPVOID>(this),
                0,
                &mThread_ID);
			if (mThread == NULL)
				throw ThreadException("fail CreateThread()");
		}

		void wait(void **retVal = NULL) {
            if (WaitForSingleObject(mThread, INFINITE) != WAIT_OBJECT_0)
                throw ThreadException("fail WaitForSingleObject()");
            else if (!CloseHandle(mThread))
                throw ThreadException("fail CloseHandle()");
            DWORD ret;
            GetExitCodeThread(mThread, &ret);
            if (ret && retVal)
                *retVal = reinterpret_cast<void*>(ret);
		}

		void *start(void) {
			(*mCallObj)(this->mFctParam);
			return NULL;
		}

        void cancel(void) {
            if (TerminateThread(mThread, 0) == 0)
                throw ThreadException("fail TerminateThread()");
        }

        void exit(void *status)	{
			if (mThread)
    			ExitThread(reinterpret_cast<DWORD>(status));
		}

	// attributes
	private:
		HANDLE mThread;
		DWORD mThread_ID;
		U mCallObj;
		T mFctParam;

};
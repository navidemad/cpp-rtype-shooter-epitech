#pragma once

#include "IThread.hpp"
#include "ThreadException.hpp"
#include "NoCopyable.hpp"
#include <WinSock2.h>
#include <iostream>

template <typename U, typename T>
class WindowsThread : public NoCopyable, public IThread<U, T> {

	// ctor dtor
	public:
		WindowsThread(void) = default;
		~WindowsThread(void) = default;

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

		void wait(void) {
			if (WaitForSingleObject(mThread, INFINITE) != WAIT_OBJECT_0)
				throw ThreadException("fail WaitForSingleObject()");
			else if (!CloseHandle(mThread))
				throw ThreadException("fail CloseHandle()");
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

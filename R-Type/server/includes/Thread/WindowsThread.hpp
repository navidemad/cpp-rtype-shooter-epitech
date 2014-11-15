#pragma once

#include "IThread.hpp"
#include <windows.h>
#include "ThreadException.hpp"

template <typename U, typename T>
class WindowsThread : public IThread<U, T> {

	// ctor dtor
	public:
		WindowsThread(void) : mState(Thread::State::NOT_CREATED) {}
		~WindowsThread(void)
		{
			if (TerminateThread(mThread, -1) == 0)
				throw ThreadException("fail TerminateThread()");
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
		IThread::State getState(void) const {
			return mState;
		}

		void create(U callObj, T fctParam) {
			mCallObj  = callObj;
			mFctParam = fctParam;

			mThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)start_thread_trampoline<U, T>, (LPVOID)this, 0, 0);
			if (mThread == NULL)
				throw ThreadException("fail CreateThread()");

			mState = Thread::State::IN_EXECUTION;
		}

		void wait(void *retVal = NULL) {
			WaitForSingleObject(mThread, INFINITE);

			mState = Thread::State::HAS_FINISHED;
		}

		void *start(void) {
			(*mCallObj)(this->mFctParam);
			return NULL;
		}

	// attributes
	private:
		HANDLE mThread;
		Thread::State mState;
		U mCallObj;
		T mFctParam;

};

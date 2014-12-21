#pragma once

#include "IThread.hpp"
#include "ThreadException.hpp"
#include "NoCopyable.hpp"
#include <pthread.h>
#include <iostream>

template <typename U, typename T>
class UnixThread : public NoCopyable, public IThread<U, T> {

	// ctor dtor
	public:
		UnixThread(void) : mIsRunning(false) {}
		~UnixThread(void) = default;

	// enum ret value
	public:
		enum : unsigned char { PTHREAD_SUCCESS = 0 };

	// interface implementation
	public:
		void create(U callObj, T fctParam) {
			mCallObj  = callObj;
			mFctParam = fctParam;

			if (pthread_create(&mThread, NULL, start_thread_trampoline<U, T>, this) != UnixThread::PTHREAD_SUCCESS)
				throw ThreadException("fail pthread_create()");

			mIsRunning = true;
		}

		void wait(void **retVal = NULL) {
			if (pthread_join(mThread, retVal) != UnixThread::PTHREAD_SUCCESS)
				throw ThreadException("fail pthread_join()");

			mIsRunning = false;
		}

		void *start(void) {
			(*mCallObj)(this->mFctParam);
			return NULL;
		}

		void cancel(void) {
			if (mIsRunning == true && pthread_cancel(mThread) != UnixThread::PTHREAD_SUCCESS)
				throw ThreadException("fail pthread_cancel()");

			mIsRunning = false;
    	}

		void exit(void *status) {
			pthread_exit(status);
			mIsRunning = false;
		}

	// attributes
	private:
		pthread_t mThread;
		U mCallObj;
		T mFctParam;
		bool mIsRunning;

};

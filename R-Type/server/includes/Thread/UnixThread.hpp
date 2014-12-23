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
		UnixThread(void) = default;
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
		}

		void wait(void) {
		  if (pthread_join(mThread, NULL) != UnixThread::PTHREAD_SUCCESS)
		  		throw ThreadException("fail pthread_join()");
		}

		void *start(void) {
			(*mCallObj)(this->mFctParam);
			return NULL;
		}

		void cancel(void) {
			if (pthread_cancel(mThread) != UnixThread::PTHREAD_SUCCESS)
				throw ThreadException("fail pthread_cancel()");
		}

		void exit(void *status) {
			pthread_exit(status);
		}

	// attributes
	private:
		pthread_t mThread;
		U mCallObj;
		T mFctParam;

};

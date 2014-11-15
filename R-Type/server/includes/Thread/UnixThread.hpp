#pragma once

#include "IThread.hpp"
#include <pthread.h>
#include "ThreadException.hpp"

template <typename U, typename T>
class UnixThread : public IThread<U, T> {

	// ctor dtor
	public:
		UnixThread(void) : mState(Thread::State::NOT_CREATED) {}
		~UnixThread(void) {}

	// copy / move operators
	public:
		UnixThread(const UnixThread &) = delete;
		UnixThread(const UnixThread &&) = delete;
		const UnixThread &operator=(const UnixThread &) = delete;
		const UnixThread &operator=(const UnixThread &&) = delete;

	// enum ret value
	public:
		enum : unsigned char { PTHREAD_SUCCESS = 0 };

	// interface implementation
	public:
		Thread::State getState(void) const {
			return mState;
		}

		void create(U callObj, T fctParam) {
			mCallObj  = callObj;
			mFctParam = fctParam;

			if (pthread_create(&mThread, NULL, start_thread_trampoline<U, T>, this) != UnixThread::PTHREAD_SUCCESS)
				throw ThreadException("fail pthread_create()");

			mState = Thread::State::IN_EXECUTION;
		}

		void wait(void **retVal = NULL) {
			if (pthread_join(mThread, retVal) != UnixThread::PTHREAD_SUCCESS)
				throw ThreadException("fail pthread_join()");

			mState = Thread::State::HAS_FINISHED;
		}

		void *start(void) {
			(*mCallObj)(this->mFctParam);
			return NULL;
		}

        void exit(void *status)
        {
            pthread_exit(status);
        }

	// attributes
	private:
		pthread_t mThread;
		Thread::State mState;
		U mCallObj;
		T mFctParam;

};

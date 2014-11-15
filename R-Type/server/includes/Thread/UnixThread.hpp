#pragma once

#include "IThread.hpp"
#include <pthread.h>
#include "ThreadException.hpp"

template <typename U, typename T>
class UnixThread : public IThread<U, T> {

	// ctor dtor
	public:
		UnixThread(void) {}
		~UnixThread(void) {
			cancel();
		}

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
		void create(U callObj, T fctParam) {
			mCallObj  = callObj;
			mFctParam = fctParam;

			if (pthread_create(&mThread, NULL, start_thread_trampoline<U, T>, this) != UnixThread::PTHREAD_SUCCESS)
				throw ThreadException("fail pthread_create()");
		}

		void wait(void **retVal = NULL) {
			if (pthread_join(mThread, retVal) != UnixThread::PTHREAD_SUCCESS)
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

#pragma once

#include "IMutex.hpp"
#include "ICondVar.hpp"
#include "CondVarException.hpp"

class UnixCondVar : public ICondVar {

	// ctor dtor
	public:
		UnixCondVar(void);
		~UnixCondVar(void);

	// copy / move operators
	public:
		UnixCondVar(const UnixCondVar &) = delete;
		UnixCondVar(const UnixCondVar &&) = delete;
		const UnixCondVar &operator=(const UnixCondVar &) = delete;
		const UnixCondVar &operator=(const UnixCondVar &&) = delete;

	// interface implementation
	public:
        void wait(std::shared_ptr<IMutex>);
		void notifyOne(void);
		void notifyAll(void);

	// attributes
	private:
		pthread_cond_t mCondVar;

};

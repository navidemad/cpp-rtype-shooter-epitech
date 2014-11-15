#pragma once

#include "IMutex.hpp"
#include "ICondVar.hpp"
#include "CondVarException.hpp"

# include <WinSock2.h>

class WindowsCondVar : public ICondVar {

	// ctor dtor
	public:
		WindowsCondVar(void);
		~WindowsCondVar(void);

	// copy / move operators
	public:
		WindowsCondVar(const WindowsCondVar &) = delete;
		WindowsCondVar(const WindowsCondVar &&) = delete;
		const WindowsCondVar &operator=(const WindowsCondVar &) = delete;
		const WindowsCondVar &operator=(const WindowsCondVar &&) = delete;

	// interface implementation
	public:
		void wait(IMutex *);
		void signal(void);
		void broadcast(void);

    // attributes
    private:
        HANDLE mCondVar;
};

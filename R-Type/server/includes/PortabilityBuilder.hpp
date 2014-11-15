#pragma once

#include <memory>
#include "IMutex.hpp"
#include "IThread.hpp"
#include "ICondVar.hpp"
#include "IClientSocket.hpp"
#include "IServerSocket.hpp"

#ifdef __unix__
# include <sys/select.h>
# include <sys/time.h>
# include <unistd.h>
# include "UnixThread.hpp"
# include "UnixMutex.hpp"
# include "UnixTcpClient.hpp"
# include "UnixTcpServer.hpp"
# include "UnixUdpClient.hpp"
# include "UnixCondVar.hpp"
#elif defined(_WIN32) || defined(WIN32)
# define sleep(t) Sleep(1000*(t))
# include <winsock2.h>
# include <time.h>
# include "WindowsThread.hpp"
# include "WindowsMutex.hpp"
# include "WindowsTcpClient.hpp"
# include "WindowsTcpServer.hpp"
# include "WindowsUdpClient.hpp"
# include "WindowsCondVar.hpp"
#endif

namespace PortabilityBuilder {

    std::shared_ptr<IMutex>			getMutex(void);
    std::shared_ptr<IClientSocket> 	getTcpClient(void);
    std::shared_ptr<IClientSocket> 	getUdpClient(void);
    std::shared_ptr<IServerSocket> 	getTcpServer(void);
    std::shared_ptr<ICondVar>       getCondVar(void);
    template <typename U, typename T>
    std::shared_ptr<IThread<U, T>> getThread(void)
    {
#ifdef __unix__
		return std::make_shared<UnixThread<U, T>>();
#elif defined(_WIN32) || defined(WIN32)
		return std::make_shared<WindowsThread<U, T>>();
#endif
    }

}

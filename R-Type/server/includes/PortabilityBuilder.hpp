#pragma once

#include <memory>
#include "IMutex.hpp"
#include "Thread/IThread.hpp"
#include "IClientSocket.hpp"
#include "IServerSocket.hpp"

#ifdef __unix__
# include "Thread/ThreadUnix.hpp"
# include "UnixMutex.hpp"
# include "UnixTcpClient.hpp"
# include "UnixTcpServer.hpp"
# include "UnixUdpClient.hpp"
#elif defined(_WIN32) || defined(WIN32)
# include "Thread/ThreadWindows.hpp"
# include "WindowsMutex.hpp"
# include "WindowsTcpClient.hpp"
# include "WindowsTcpServer.hpp"
# include "WindowsUdpClient.hpp"
#endif

namespace PortabilityBuilder {

	std::shared_ptr<IMutex>					getMutex(void);
	std::shared_ptr<IClientSocket> 	getTcpClient(void);
	std::shared_ptr<IClientSocket> 	getUdpClient(void);
	std::shared_ptr<IServerSocket> 	getTcpServer(void);
	std::shared_ptr<IThread> 				getThread(void);	

}

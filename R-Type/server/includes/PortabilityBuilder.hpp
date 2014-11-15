#pragma once

#include <memory>
#include "IMutex.hpp"
#include "IThread.hpp"
#include "IClientSocket.hpp"
#include "IServerSocket.hpp"

#ifdef __unix__
# include "UnixThread.hpp"
# include "UnixMutex.hpp"
# include "UnixTcpClient.hpp"
# include "UnixTcpServer.hpp"
# include "UnixUdpClient.hpp"
#elif defined(_WIN32) || defined(WIN32)
# include "WindowsThread.hpp"
# include "WindowsMutex.hpp"
# include "WindowsTcpClient.hpp"
# include "WindowsTcpServer.hpp"
# include "WindowsUdpClient.hpp"
#endif

namespace PortabilityBuilder {

	std::shared_ptr<IMutex>			getMutex(void);
	std::shared_ptr<IClientSocket> 	getTcpClient(void);
	std::shared_ptr<IClientSocket> 	getUdpClient(void);
	std::shared_ptr<IServerSocket> 	getTcpServer(void);
	template <typename U, typename T>
	std::shared_ptr<IThread<U, T>> getThread(void)
	{
		#ifdef __unix__
			return std::shared_ptr<IThread<U, T>>(new UnixThread<U, T>);
		#elif defined(_WIN32) || defined(WIN32)
			return std::shared_ptr<IThread<U, T>>(new WindowsThread<U, T>);
		#endif
	}

}

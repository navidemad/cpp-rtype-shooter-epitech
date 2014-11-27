#pragma once

#include "Config.hpp"
#include "IMutex.hpp"
#include "IThread.hpp"
#include "ICondVar.hpp"
#include "IClientSocket.hpp"
#include "IServerSocket.hpp"
#include "IDynLib.hpp"
#include "WindowsThread.hpp"
#include "NoCopyable.hpp"

#include <memory>

namespace PortabilityBuilder {

    std::shared_ptr<IMutex>			getMutex(void);
	std::shared_ptr<IClientSocket> 	getTcpClient(void);
	std::shared_ptr<IClientSocket> 	getUdpClient(void);
	std::shared_ptr<IServerSocket> 	getTcpServer(void);
	std::shared_ptr<ICondVar>       getCondVar(void);
    std::shared_ptr<IDynLib>        getDynLib(void);

	template <typename U, typename T>
    std::shared_ptr<IThread<U, T>>  getThread(void) {
		return std::make_shared<WindowsThread<U, T>>();
    }

}

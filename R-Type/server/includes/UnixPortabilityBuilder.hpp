#pragma once

#include "Config.hpp"
#include "IMutex.hpp"
#include "IThread.hpp"
#include "ICondVar.hpp"
#include "IClientSocket.hpp"
#include "IServerSocket.hpp"

# include "UnixThread.hpp"
# include "UnixMutex.hpp"
# include "UnixTcpClient.hpp"
# include "UnixTcpServer.hpp"
# include "UnixUdpClient.hpp"
# include "UnixCondVar.hpp"

#include <memory>

namespace PortabilityBuilder {

    std::shared_ptr<IMutex>			getMutex(void);
    std::unique_ptr<IClientSocket> 	getTcpClient(void);
    std::unique_ptr<IClientSocket> 	getUdpClient(void);
    std::unique_ptr<IServerSocket> 	getTcpServer(void);
    std::unique_ptr<ICondVar>       getCondVar(void);
    template <typename U, typename T>
    std::shared_ptr<IThread<U, T>>  getThread(void)
    {
		return std::make_shared<UnixThread<U, T>>();
    }

}

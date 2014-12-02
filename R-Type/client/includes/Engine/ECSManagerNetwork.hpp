#pragma once

class RTypeClient;

#include <vector>
#include <list>
#include <stdint.h>
#include "Entity.hpp"
#include "Component.hpp"
#include "../Core/System.hpp"
#include "ECSManager.hpp"
#include "Network/ServerCommunication.hpp"

class ECSManagerNetwork : public ECSManager, public ServerCommunication::OnServerEvent
{
public:
	void		start();
	void		stop();
};

#include "ECSManager.h"
#include "RTypeClient.h"


ECSManager::ECSManager(RType &client)
: mClient(client)
{
}


ECSManager::~ECSManager()
{
}

RType &ECSManager::getClient() const {
	return mClient;
}
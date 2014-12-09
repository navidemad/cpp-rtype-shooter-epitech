#pragma once

#include "RTypeClient.h"

class RType;

class ECSManager
{
public: // ctor dtor
	ECSManager(RType &);
	virtual ~ECSManager();
	
public: // getter
	RType &getClient() const;
	
private: // private attribute
	RType &mClient;
};


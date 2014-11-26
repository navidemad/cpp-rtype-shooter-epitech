#include <iostream>
#include "RTypeClient.hpp"

#include <QApplication>
#include "Network/ServerCommunication.hpp"

int trySocket(int ac, char **av){
	QApplication	app(ac, av);
	
	ServerCommunication server;

	server.setServerTcp(4242, "127.0.0.1");
	server.connectSocketTcp();

	return app.exec();
}

int		main(int ac, char **av)
{
	//return trySocket(ac, av);
	RTypeClient	app;

	app.run();
	return (0);
}

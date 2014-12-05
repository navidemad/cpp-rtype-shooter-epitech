#include "RTypeClient.hpp"

#include <QApplication>
#include "Network/ServerCommunication.hpp"

int trySocket(int ac, char **av){
	QApplication	app(ac, av);
	
	ServerCommunication server;
	try {
	server.setServerTcp(4244, "10.41.173.139");
	server.connectSocketTcp();
	}

	catch (...){

	}
	return app.exec();
}

int		main(int ac, char ** av)
{
	return trySocket(ac, av);
	RTypeClient	app;

	app.run();
	return (0);
}

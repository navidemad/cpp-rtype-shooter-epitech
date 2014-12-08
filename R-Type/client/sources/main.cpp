#include "RTypeClient.hpp"

#include <QApplication>

int		main(int ac, char ** av)
{
	QApplication	app(ac, av);

	RTypeClient		rtype;
	rtype.run();

	return app.exec();
}

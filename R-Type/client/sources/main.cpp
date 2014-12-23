#include <QtCore>
#include "IResource.hpp"
#include "RTypeClient.hpp"

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(IResource::Direction)

#include <iostream>

int main(int ac, char **av)
{
	try {
		QCoreApplication app(ac, av);

		qRegisterMetaType<std::string>();
		qRegisterMetaType<IResource::Direction>();
		RTypeClient		rtype;
		QObject::connect(&rtype, SIGNAL(finished()), &app, SLOT(quit()));

		rtype.start();
		return app.exec();
	}
	catch (std::exception &exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

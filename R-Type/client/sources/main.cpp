/*
#include "PortabilityBuilder.hpp"
#include "IResource.hpp"
#include "DynLibException.hpp"

#include <iostream>

int main(void)
{
	try {
		auto lib = PortabilityBuilder::getDynLib();
		try {
			lib->libraryLoad(std::string("../../shared/entities/Monster/build/Debug/Monster"));
			auto ressource = reinterpret_cast<IResource*(*)(void)>(lib->functionLoad("entry_point"))();
			std::cout << ressource->getSpeed() << std::endl;
		}
		catch (const DynLibException& e) {
			std::cout << e.what() << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}
*/

#include <QtCore>
#include "IResource.hpp"
#include "RTypeClient.hpp"

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(IResource::Direction)

int main(int ac, char **av)
{
    QCoreApplication app(ac, av);

    qRegisterMetaType<std::string>();
	qRegisterMetaType<IResource::Direction>();
    RTypeClient		rtype;
    QObject::connect(&rtype, SIGNAL(finished()), &app, SLOT(quit()));

    rtype.start();
	return app.exec();
}

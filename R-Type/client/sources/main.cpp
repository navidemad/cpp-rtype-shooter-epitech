/*
#include "PortabilityBuilder.hpp"
#include "IResource.hpp"
#include "DynLibException.hpp"

#include <iostream>

int main(void)
{
	auto lib = PortabilityBuilder::getDynLib();
	try {
		lib->libraryLoad(std::string("./../shared/entities/Monster/Monster"));
		auto ressource = reinterpret_cast<IResource*(*)(void)>(lib->functionLoad("entry_point"))();
		std::cout << ressource->getSpeed() << std::endl;
	}
	catch (const DynLibException& e) {
		std::cout << e.what() << std::endl;
	}
    #if defined(__OS_WINDOWS__)
        system("PAUSE");
    #endif
	return 0;
}
*/

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

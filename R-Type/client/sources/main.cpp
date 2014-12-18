#include <QtCore>
#include "IResource.hpp"
#include "RTypeClient.hpp"
#include "DynLib/WindowsDynLib.hpp"

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(IResource::Direction)

int main(int ac, char **av)
{
	/*
	auto            lib = new WindowsDynLib;
	void*           fctPtr;

	lib->libraryLoad(std::string("entity/LOL"));
	fctPtr = lib->functionLoad("test");
	std::cout << fctPtr << std::endl;
	((void(*)(void))fctPtr)();
	*/
    QCoreApplication app(ac, av);

    qRegisterMetaType<std::string>();
	qRegisterMetaType<IResource::Direction>();
    RTypeClient		rtype;
    QObject::connect(&rtype, SIGNAL(finished()), &app, SLOT(quit()));

    rtype.start();
	return app.exec();
}

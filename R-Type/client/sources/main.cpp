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

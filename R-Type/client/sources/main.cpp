#include "RTypeClient.hpp"
#include <QtCore>

int main(int ac, char **av)
{
    QCoreApplication app(ac, av);

    RTypeClient		rtype;
    QObject::connect(&rtype, SIGNAL(finished()), &app, SLOT(quit()));

    rtype.start();
    return app.exec();
}

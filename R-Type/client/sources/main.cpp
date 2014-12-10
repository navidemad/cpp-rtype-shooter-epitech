#include "RTypeClient.hpp"
#include <QtCore>

Q_DECLARE_METATYPE(std::string)

int main(int ac, char **av)
{
    QCoreApplication app(ac, av);

    qRegisterMetaType<std::string>();
    
    RTypeClient		rtype;
    QObject::connect(&rtype, SIGNAL(finished()), &app, SLOT(quit()));

    rtype.start();
    return app.exec();
}

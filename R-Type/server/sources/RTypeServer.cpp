#include "RTypeServer.hpp"
#include "PortabilityBuilder.hpp"

/*
#include "DynLibException.hpp"
#include <iostream>

class IPlayer
{
public:
    virtual double getSpeed() = 0;
    virtual ~IPlayer() {}
};

typedef IPlayer * (*monsterCall) (unsigned int screenWidth, unsigned int screenHeight,
    unsigned int amplitude, unsigned int origine, unsigned int nbOscillation);
*/

RTypeServer::RTypeServer(void) {

}

RTypeServer::~RTypeServer(void) {

}

int RTypeServer::run(void) {
    /*
    auto        lib = PortabilityBuilder::getDynLib();
    void*       fct;
    IPlayer*    monster;

    lib->libraryLoad(std::string("./build/tinymonster"));
    fct = lib->functionLoad("createAndFill");

    monster = ((monsterCall)(fct))(800, 600, 100, 100, 1);
    std::cout << monster << std::endl;

    std::cout << monster->getSpeed() << std::endl;
    */
    return 1;
}

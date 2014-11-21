#include "WinDynaLib.hpp"
#include "IPlayer.h"

typedef IPlayer * (*monsterCall) (unsigned int screenWidth, unsigned int screenHeight,
                    unsigned int amplitude, unsigned int origine, unsigned int nbOscillation);

int main()
{
    WinDynaLib  _lib;
    void *fct;
    IPlayer *monster;

    try{

    _lib.dynaLoad("tinymonster.dll");
    fct = _lib.funcLoad("create");
    std::cout << (int) fct << std::endl;
    monster =
               ((monsterCall) (fct))(1,1,1,1,1);
    std::cout << monster->getSpeed() << std::endl;
    }
    catch (Exception *e)
    {
        std::cout << e->what() << std::endl;
    }
}

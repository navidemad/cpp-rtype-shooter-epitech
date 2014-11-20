#include "RTypeServer.hpp"

#include <iostream>

int	main(void) {
    int ret;
    try 
    {
        RTypeServer server;
        ret = server.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        ret = - 1;
    }
    system("PAUSE>NUL");
    return ret;
}

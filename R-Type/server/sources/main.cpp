/*
#include "RTypeServer.hpp"
#include "ScriptLoader.hpp"
#include "ScopedLock.hpp"
#include "PortabilityBuilder.hpp"
#include <iostream>
#include <cstdio>

int main(void) {
    auto mutex = PortabilityBuilder::getMutex();


    // test 1 AVEC DEADLOCK
    {
        Scopedlock(mutex);
        {
            Scopedlock(mutex);
            {

            }
        }
    }


    // test 1 SANS DEADLOCK
    {
        Scopedlock(mutex);
        {

        }
    }


    {
        Scopedlock(mutex);
        {

        }
    }


    return 0;
}
*/

#include "RTypeServer.hpp"
#include "ScriptLoader.hpp"
#include <iostream>

int main(void) {
    int ret;

    try {
        RTypeServer server;
        server.run();
        ret = EXIT_SUCCESS;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        ret = EXIT_FAILURE;
    }
    #if defined(__OS_WINDOWS__)
        system("PAUSE");
    #endif
    return ret;
}

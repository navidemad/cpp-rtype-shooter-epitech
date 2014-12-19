/*
#include "RTypeServer.hpp"
#include "ScriptLoader.hpp"
#include <iostream>

int main(void) {
    ScriptLoader mScriptLoader;
    mScriptLoader.loadAll();
    #if defined(__OS_WINDOWS__)
        system("PAUSE");
    #endif
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

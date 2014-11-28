#include "RTypeServer.hpp"
#include "ScriptLoader.hpp"
#include <iostream>

int	main(void) {
/*	ScriptLoader loader;

	loader.loadScript("./sources/Script/Simon.txt");
	#if defined(__OS_WINDOWS__)
		system("PAUSE");
	#endif
*/
    int ret;
    try 
    {
        RTypeServer server;
        server.run();
        ret = EXIT_SUCCESS;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        ret = EXIT_FAILURE;
    }
    #if defined(__OS_WINDOWS__)
        system("PAUSE");
    #endif
    return ret;
}

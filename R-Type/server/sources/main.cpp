/*
#include "PortabilityBuilder.hpp"
int main(void) {
	auto mReaddir = PortabilityBuilder::getReaddir();
	mReaddir->readFolder("C:/Users/LikseN/Desktop/R-Type/R-Type/server/Test/");
	#if defined(__OS_WINDOWS__)
		system("PAUSE");
	#endif
}
*/

/*
#include <vector>
#include <string>
#include <iostream>
int main(void) {
	std::vector<std::string> mGames;
	mGames.push_back("A");
	mGames.push_back("B");
	mGames.push_back("C");
	for (auto it = mGames.begin(); it != mGames.end();) {
		std::cout << *it << std::endl;
		it = mGames.erase(it);
	}
	#if defined(__OS_WINDOWS__)
		system("PAUSE");
	#endif
	return 0;
}
*/

#include "RTypeServer.hpp"
#include "ScriptLoader.hpp"
#include <iostream>
int	main(void) {
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

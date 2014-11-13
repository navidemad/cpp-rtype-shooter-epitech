#include "Thread/Thread.hpp"

#include <iostream>

int	main(void)
{
    int ret;
    try 
    {
        auto thread = Thread::getInstance();
        ret = 0;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        ret = - 1;
    }
    system("PAUSE>NUL");
    return ret;
}

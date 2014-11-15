#include "PortabilityBuilder.hpp"

#include <iostream>

class functor_test_1
{
    public:
        void operator()(int index) const
        {
            std::cout << "[" << __FUNCTION__ << "]\t We are on index '" << index << "'" << std::endl;
        }
};

int main(void) {
	PortabilityBuilder::getThread<functor_test_1*, int>();
	return 0;
}
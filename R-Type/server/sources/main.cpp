#include <iostream>
#include "ThreadPool.hpp"

void fct(void) {
	std::cout << "work done" << std::endl;
}

int main(void) {
	ThreadPool pool(5);

	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;
	pool << fct;

	while (true);
}

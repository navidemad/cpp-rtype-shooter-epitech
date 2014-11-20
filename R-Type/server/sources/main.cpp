#include <iostream>
#include "ThreadPool.hpp"
#include "Observer.hpp"

void fct(void) {
	std::cout << "work done" << std::endl;
}

class Test {

	public:
		enum class Events {
			SIMPLE_EVENT
		};

	public:
		void registerObserver(Events e, std::function<void()> fct) {
			observer.registerObserver(e, fct);
		}

		void notifyObserver(Events e) {
			observer.notifyObservers(e);
		}

	private:
		Observer<Events> observer;

};

void test(void) {
	std::cout << "TEST OK" << std::endl;
}

int main(void) {
	Test t;

	t.registerObserver(Test::Events::SIMPLE_EVENT, test);
	t.registerObserver(Test::Events::SIMPLE_EVENT, test);
	t.registerObserver(Test::Events::SIMPLE_EVENT, test);
	t.notifyObserver(Test::Events::SIMPLE_EVENT);

	system("PAUSE");

	return 0;
}

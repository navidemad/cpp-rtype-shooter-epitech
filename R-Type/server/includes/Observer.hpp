#pragma once

#include <map>
#include <vector>
#include <functional>

template <typename T>
class Observer {

	// ctor - dtor
	public:
		Observer(void) {}
		~Observer(void) {}

	// move - copy operators
	public:
		Observer(const Observer &) = delete;
		Observer(const Observer &&) = delete;
		const Observer &operator=(const Observer &) = delete;
		const Observer &operator=(const Observer &&) = delete;

	// handle observers
	public:
		void	registerObserver(T event, const std::function<void()> &callback) {
			mObservers[event].push_back(callback);
		}

		void	notifyObservers(T event) {
			if (mObservers.find(event) != mObservers.end())
				for (const auto &fct : mObservers[event])
					fct();
		}

	// attributes
	private:
		std::map<T, std::vector<std::function<void()>>> mObservers;

};

/*
 * observer.cpp
 *
 *  Created on: 3 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "Observer.h"

#include <algorithm>
#include <iterator>

template<typename ... Type>
Observer<Type...>::Observer() {
}

template<typename ... Type>
Observer<Type...>::~Observer() {
	for (typename std::vector<Observable<Type...>*>::iterator it =
			observables.end() - 1; it != observables.begin() - 1; --it) {
		observables.erase(it);
		(*it)->removeObserver(*this);
	}
}

template<typename ... Type>
void Observer<Type...>::addObservable(Observable<Type...>& observable) {
	if (std::find(observables.begin(), observables.end(), observable)
			== observables.end()) {
		observables.push_back(&observable);
		observable.addObserver(*this);
	}
}

template<typename ... Type>
void Observer<Type...>::removeObservable(Observable<Type...>& observable) {
	typename std::vector<Observable<Type...>*>::iterator it;

	if ((it = std::find(observables.begin(), observables.end(), observable))
			!= observables.end()) {
		observables.erase(it);
		(*it)->removeObserver(*this);
	}
}

template<typename ... Type>
bool operator==(Observable<Type...>* leftObservable,
		const Observable<Type...>& rightObservable) {
	return leftObservable == &rightObservable;
}

#include "Observer.cxx"

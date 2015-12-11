/*
 * Observable.cpp
 *
 *  Created on: 3 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "Observable.h"
#include <algorithm>

template<typename ... Type>
Observable<Type...>::Observable() {
}

template<typename ... Type>
Observable<Type...>::~Observable() {
	for (typename std::vector<Observer<Type...>*>::iterator it = observers.end()
			- 1; it != observers.begin() - 1; --it) {
		observers.erase(it);
		(*it)->removeObservable(*this);
	}
}

template<typename ... Type>
void Observable<Type...>::addObserver(Observer<Type...>& observer) {
	if (std::find(observers.begin(), observers.end(), observer)
			== observers.end()) {
		observers.push_back(&observer);
		observer.addObservable(*this);
	}
}

template<typename ... Type>
void Observable<Type...>::removeObserver(Observer<Type...>& observer) {
	typename std::vector<Observer<Type...>*>::iterator it;

	if ((it = std::find(observers.begin(), observers.end(), observer))
			!= observers.end()) {
		observers.erase(it);
		(*it)->removeObservable(*this);
	}
}

template<typename ... Type>
void Observable<Type...>::notify(Type ... args) {
	for (typename std::vector<Observer<Type...>*>::iterator it =
			observers.begin(); it != observers.end(); ++it)
		(*it)->update(*this, args...);
}

template<typename ... Type>
bool operator==(Observer<Type...>* leftObserver,
		const Observer<Type...>& rightObserver) {
	return leftObserver == &rightObserver;
}

#include "Observable.cxx"

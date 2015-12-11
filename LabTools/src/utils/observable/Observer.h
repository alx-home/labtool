/*
 * Observer.h
 *
 *  Created on: 3 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_OBSERVABLE_OBSERVER_H_
#define SRC_UTILS_OBSERVABLE_OBSERVER_H_

#include "Observable.h"
#include <vector>

template<typename ... Type>
class Observable;

template<typename ... Type>
class Observer {
private:
	std::vector<Observable<Type ...>*> observables = std::vector<
			Observable<Type ...>*>();

public:
	Observer();
	virtual ~Observer();

	virtual void addObservable(Observable<Type...>& observable);
	virtual void removeObservable(Observable<Type...>& observable);

	virtual void update(Observable<Type...>& observable, Type ... args) = 0;
};

#endif /* SRC_UTILS_OBSERVABLE_OBSERVER_H_ */

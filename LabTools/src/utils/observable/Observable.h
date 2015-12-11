/*
 * Observable.h
 *
 *  Created on: 3 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_UTILS_OBSERVABLE_OBSERVABLE_H_
#define SRC_UTILS_OBSERVABLE_OBSERVABLE_H_

#include <vector>

#include "Observer.h"

template<typename ... Type>
class Observer;

template<typename ... Type>
class Observable {
private:
	std::vector<Observer<Type...>*> observers = std::vector<Observer<Type...>*>();
public:
	Observable();
	virtual ~Observable();

	virtual void addObserver(Observer<Type...>& observer);
	virtual void removeObserver(Observer<Type...>& observer);

	virtual void notify(Type ... args);
};

#endif /* SRC_UTILS_OBSERVABLE_OBSERVABLE_H_ */

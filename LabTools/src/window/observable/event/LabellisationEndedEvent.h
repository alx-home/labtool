/*
 * LabellisationEndedEvent.h
 *
 *  Created on: 7 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_OBSERVABLE_EVENT_LABELLISATIONENDEDEVENT_H_
#define SRC_WINDOW_OBSERVABLE_EVENT_LABELLISATIONENDEDEVENT_H_

#include <string>
#include <vector>

#include "Event.h"

namespace window {
namespace observable {

class LabellisationEndedEvent: public Event {
public:
	LabellisationEndedEvent();
	virtual ~LabellisationEndedEvent();

	typedef enum {
		LOW, HIGHT
	} Probability;

	class Pair {
	public:
		Pair(const std::string& sceneName, const std::string& modelName,
				double proba);
		~Pair();
		const std::string& getSceneName() const;
		const std::string& getModelName() const;
		double getProba() const;

	private:
		std::string sceneName;
		std::string modelName;
		double proba;
	};

	void addCorrespondance(const std::string& sceneName,
			const std::string& modelName, double proba);
	const std::vector<Pair>& getCorespondances() const;

private:
	std::vector<Pair> datas = std::vector<Pair>();
};

} /* namespace observable */
} /* namespace window */

#endif /* SRC_WINDOW_OBSERVABLE_EVENT_LABELLISATIONENDEDEVENT_H_ */

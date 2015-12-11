/*
 * LabellisationEndedEvent.cpp
 *
 *  Created on: 7 déc. 2015
 *      Author: Alexandre GARCIN
 */

#include "LabellisationEndedEvent.h"

namespace window {
namespace observable {

LabellisationEndedEvent::LabellisationEndedEvent() {
}

LabellisationEndedEvent::~LabellisationEndedEvent() {
}

void LabellisationEndedEvent::addCorrespondance(const std::string& sceneName, const std::string& modelName, double proba) {
	datas.push_back(LabellisationEndedEvent::Pair(sceneName, modelName, proba));
}

const std::vector<LabellisationEndedEvent::Pair>& LabellisationEndedEvent::getCorespondances() const {
	return datas;
}

LabellisationEndedEvent::Pair::~Pair() {
}

LabellisationEndedEvent::Pair::Pair(const std::string& sceneName, const std::string& modelName, double proba) :
		sceneName(sceneName), modelName(modelName), proba(proba) {
}

const std::string& LabellisationEndedEvent::Pair::getSceneName() const {
	return sceneName;
}

const std::string& LabellisationEndedEvent::Pair::getModelName() const {
	return modelName;
}

double LabellisationEndedEvent::Pair::getProba() const {
	return proba;
}

}
/* namespace observable */
} /* namespace window */

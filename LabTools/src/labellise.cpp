/*
 * labelise.cpp
 *
 *  Created on: 26 oct. 2015
 *      Author: Alexandre GARCIN
 */

#include "labellise.hpp"

#include <gmmreg_api/gmmreg_cpd.h>
#include <climits>
#include <cmath>
#include <exception>
#include <iostream>
#include <utility>

#include "exception/labellisation/LostPointFrameLowerLimitReachedException.h"
#include "exception/labellisation/LostPointFrameUpperLimitReachedException.h"
#include "utils/c3d/writter/Writter.h"
#include "utils/observable/Observable.h"
#include "utils/xml/Reader.h"
#include "utils/xml/Writter.h"
#include "window/observable/event/LabellisationEndedEvent.h"
#include "window/Window.h"
#include "Language/LanguageLoader.h"

extern std::string sceneLabelUnlabelisedPrefix;

Labeliser::~Labeliser() {
}

Labeliser::Labeliser(std::unordered_map<std::string, generic::DataStruct>& inputModel,
		std::unordered_map<std::string, generic::DataStruct>& inputScene,
		const std::unordered_map<std::string, std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>>& estimationSets, const std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>& groupMarkers,
std::vector<std::tuple<std::string, labeliser::Box>>& labelisationBoxes, unsigned int gapFramesSize, double accelerationMax, double frameRate, const std::string& modelFilePath) :
inputScene(inputScene), inputModel(), estimationSets(estimationSets), gapframes(), estimationPoints(), offPositionFrames(), nbScenePoints(
0), labelisationBoxes(), modelFilePath(modelFilePath), groupMarkers(groupMarkers), gapFramesSize(gapFramesSize), frameRate(frameRate), accelerationMax(accelerationMax) {

	for (const auto& box : labelisationBoxes)
	this->labelisationBoxes.insert(std::unordered_map<unsigned long long int, std::tuple<std::string, labeliser::Box>>::value_type (labBoxUUID.getUUID(), box));

	for (const auto& it : inputModel)
	if (!(it.first.size() > 6 && it.first.substr(0, 7) == "outlier") &&
	!(it.second.datas(0, 0) == it.second.datas(0, 1) && it.second.datas(0, 1) == it.second.datas(0, 2)
			&& it.second.datas(0, 2) == 0)) {
		auto& data = this->inputModel[it.first].datas;

		data.set_size(1, 3);
		data(0, 0) = it.second.datas(0, 0);
		data(0, 1) = it.second.datas(0, 1);
		data(0, 2) = it.second.datas(0, 2);
	}

	std::unordered_map<std::string, vnl_matrix<double>> outliers = std::unordered_map<std::string, vnl_matrix<double>>();

	for (const auto& it : inputScene)
	if (it.first.size() > 6 && it.first.substr(0, 7) == "outlier")
	outliers[it.first] = it.second.datas;

	for (const auto& outlier : outliers)
	inputScene.erase(outlier.first);

	for (const auto& outlier : outliers)
	inputScene["outlier_" + std::to_string(outlierUUID.getUUID())].datas = outlier.second;

	if (inputScene.begin()->second.datas.rows() > gapFramesSize) {
		std::stack<std::string> ghostPoints;

		for (const auto& point : inputScene) {
			unsigned int iMax = point.second.datas.rows();
			unsigned int firstFrame = 0;
			bool firstFrameSetted = false;
			unsigned int lastFrame = 0;

			for (unsigned int i = 0; i < iMax; ++i)
			if (std::isnan(point.second.datas(i, 0))) {
				if(!firstFrameSetted)
				firstFrame = i;
			}
			else {
				lastFrame = std::max(lastFrame, i);
				firstFrameSetted = true;
			}

			if (lastFrame - firstFrame < gapFramesSize)
			ghostPoints.push(point.first);
		}

		while (!ghostPoints.empty()) {
			inputScene["outlier_" + std::to_string(outlierUUID.getUUID())] = inputScene[ghostPoints.top()];
			inputScene.erase(ghostPoints.top());
			ghostPoints.pop();
		}
	}

	setCurrentFrame(0);
	setGapFrames();
	updateIncompletePoints();
}

void Labeliser::run(std::unordered_map<std::string, generic::DataStruct>& inputModel,
		std::unordered_map<std::string, generic::DataStruct>& inputScene,
		const std::unordered_map<std::string, std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>>& estimationSets, const std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>& groupMarkers,
std::vector<std::tuple<std::string, labeliser::Box>>& labelisationBoxes, unsigned int gapFramesSize, const std::string& sceneFilePath, const std::string& modelFilePath, double probaMin, double accelerationMax, double frameRate) {
	window::Window window(std::make_shared<Labeliser>(inputModel, inputScene, estimationSets, groupMarkers, labelisationBoxes, gapFramesSize, accelerationMax, frameRate, modelFilePath),
	inputScene.begin()->second.datas.rows(), probaMin, gapFramesSize, accelerationMax, frameRate);
	window.run(sceneFilePath);
}

const std::unordered_map<unsigned long long int, std::tuple<std::string, labeliser::Box>>& Labeliser::getLabelisationBoxes() const {
	return labelisationBoxes;
}

unsigned int Labeliser::getNextLostPointFrame() const {
	if (gapframes.upper_bound(currentFrame) == gapframes.end())
		throw exception::labelisation::LostPointFrameUpperLimitReachedException();

	return gapframes.upper_bound(currentFrame)->first;
}

unsigned int Labeliser::getPreviousLostPointFrame() const {
	if (gapframes.size() == 0 || gapframes.begin()->first >= currentFrame)
		throw exception::labelisation::LostPointFrameLowerLimitReachedException();

	return (--gapframes.lower_bound(currentFrame))->first;
}

bool Labeliser::isGapFrame() const {
	return gapframes.lower_bound(currentFrame) != gapframes.end() && gapframes.lower_bound(currentFrame)->first == currentFrame;
}

unsigned int Labeliser::getNbGapFrames() const {
	return gapframes.size();
}

const std::vector<std::string>& Labeliser::getNextLostPointLabels(unsigned int lowerFrame) const {
	if (gapframes.upper_bound(lowerFrame) == gapframes.end())
		throw exception::labelisation::LostPointFrameUpperLimitReachedException();

	return gapframes.upper_bound(lowerFrame)->second;
}

const std::vector<std::string>& Labeliser::getPreviousLostPointLabels(unsigned int upperFrame) const {
	if (gapframes.size() == 0 || gapframes.begin()->first >= upperFrame)
		throw exception::labelisation::LostPointFrameLowerLimitReachedException();

	return (--gapframes.upper_bound(upperFrame))->second;
}

void Labeliser::splitLabel(const std::string& label, unsigned int begginFrame, unsigned int endFrame) {
	auto& datas = inputScene[label];
	auto splitedDatas = datas;

	for (unsigned int i = begginFrame; i <= endFrame && i < datas.datas.rows(); ++i) {
		datas.datas(i, 0) = std::nan("");
		datas.datas(i, 1) = std::nan("");
		datas.datas(i, 2) = std::nan("");
	}

	for (unsigned int i = 0; i < begginFrame && i < datas.datas.rows(); ++i) {
		splitedDatas.datas(i, 0) = std::nan("");
		splitedDatas.datas(i, 1) = std::nan("");
		splitedDatas.datas(i, 2) = std::nan("");
	}

	for (unsigned int i = endFrame + 1; i < datas.datas.rows(); ++i) {
		splitedDatas.datas(i, 0) = std::nan("");
		splitedDatas.datas(i, 1) = std::nan("");
		splitedDatas.datas(i, 2) = std::nan("");
	}

	inputScene["outlier_" + std::to_string(outlierUUID.getUUID())] = splitedDatas;
}

void Labeliser::renameLabel(const std::string& oldLabel, const std::string& newLabel) {
	std::string newLabel2 = newLabel;

	if (newLabel.c_str()[0] == '{') {
		unsigned int endIndex = newLabel.find_first_of("}") + 1;
		newLabel2 = newLabel.substr(endIndex, newLabel.size() - endIndex);
		unsigned int virgulePos = newLabel.find_first_of(",");

		unsigned int begginFrame = 0;
		{
			std::stringstream begginFrame_;
			std::string tmp = newLabel.substr(1, virgulePos - 1);
			if (tmp.size()) {
				begginFrame_ << tmp;
				begginFrame_ >> begginFrame;
				if (begginFrame == 1)
					begginFrame = 0;
				else
					--begginFrame;
			}
		}

		unsigned int endFrame = getNbFrames() - 1;

		{
			std::stringstream endFrame_;
			std::string tmp = newLabel.substr(virgulePos + 1, endIndex - virgulePos - 2);

			if (tmp.size()) {
				endFrame_ << tmp;
				endFrame_ >> endFrame;
				if (endFrame == 1)
					endFrame = 0;
				else
					--endFrame;
			}
		}

		if (newLabel2.substr(0, 8) != "outlier_")
			renameLabel(oldLabel, newLabel2);
		else
			renameLabel(oldLabel, newLabel2 = "outlier_" + std::to_string(outlierUUID.getUUID()));

		splitLabel(newLabel2, begginFrame, endFrame);
		return;
	}

	auto& oldDatas = inputScene[oldLabel];

	generic::DataStruct outlier = generic::DataStruct();
	outlier.datas = vnl_matrix<double>(oldDatas.datas.rows(), oldDatas.datas.cols(), std::nan(""));

	bool colision = false;
	unsigned long long int UUID;

	if (oldLabel.size() > 7 && oldLabel.substr(0, 8) == "outlier_") {
		std::stringstream ss;
		ss << oldLabel.substr(8, oldLabel.size() - 8);
		ss >> UUID;
	} else
		UUID = outlierUUID.getUUID();

	if (inputScene.find(newLabel2) != inputScene.end()) {
		auto& collisionDatas = inputScene[newLabel2];

		for (unsigned int i = 0; i < collisionDatas.datas.rows(); ++i)
			for (unsigned int j = 0; j < collisionDatas.datas.cols(); ++j)
				if (!std::isnan(oldDatas.datas(i, j)))
					if (!std::isnan(collisionDatas.datas(i, j))) {
						outlier.datas(i, j) = oldDatas.datas(i, j);
						colision = true;
					} else
						collisionDatas.datas(i, j) = oldDatas.datas(i, j);
	} else
		inputScene[newLabel2] = oldDatas;

	/*inputScene.erase(newLabel2);
	 inputScene[newLabel2] = oldDatas;*/
	inputScene.erase(oldLabel);

	if (!colision)
		outlierUUID.freeUUID(UUID);
	else
		inputScene["outlier_" + std::to_string(UUID)] = outlier;
}

void Labeliser::erasePoint(const std::string& name) {
	//inputScene.erase(name);
	renameLabel(name, "outlier_" + std::to_string(outlierUUID.getUUID()));
}

void Labeliser::getInputDatas(unsigned int frame, vnl_matrix<double>& datas, std::vector<std::string>& labels,
		const std::unordered_map<std::string, generic::DataStruct>& input) const {
	vnl_matrix<double> datas_tmp;

	unsigned int i = 0;
	datas_tmp.set_size(input.size(), 3);

	for (const auto& data : input)
		if (!std::isnan(data.second.datas(frame, 0))) {
			datas_tmp(i, 0) = data.second.datas(frame, 0);
			datas_tmp(i, 1) = data.second.datas(frame, 1);
			datas_tmp(i, 2) = data.second.datas(frame, 2);

			labels.push_back(data.first);

			++i;
		}

	datas.set_size(i, 3);

	for (unsigned int j = 0; j < i; ++j) {
		datas(j, 0) = datas_tmp(j, 0);
		datas(j, 1) = datas_tmp(j, 1);
		datas(j, 2) = datas_tmp(j, 2);
	}
}

void Labeliser::getInputModelDatas(vnl_matrix<double>& datas, std::vector<std::string>& labels) const {
	getInputDatas(0, datas, labels, inputModel);
}

const utils::UUID& Labeliser::getLabelisationBoxesUUID() const {
	return labBoxUUID;
}

void Labeliser::rotateDatas(const ::Vector3d& axis, double angle) {
	/*	::Vector3d barycenter = ::Vector3d::center;

	 unsigned int nbDatas = 0;

	 for (const auto& data : inputScene)
	 if (!std::isnan(data.second.datas(0, 0))) {
	 unsigned int frame = modelFrame == std::numeric_limits<unsigned int>::max() ? 0. : modelFrame;

	 barycenter += ::Vector3d( { data.second.datas(frame, 0), data.second.datas(frame, 1), data.second.datas(frame, 2) });
	 ++nbDatas;
	 }

	 barycenter /= nbDatas;
	 */
	for (unsigned int i = 0; i < getNbFrames(); ++i)
		for (auto& data : inputScene)
			if (!std::isnan(data.second.datas(i, 0))) {
				::Vector3d pos;
				pos[0] = data.second.datas(i, 0);
				pos[1] = data.second.datas(i, 1);
				pos[2] = data.second.datas(i, 2);

				//	pos -= barycenter;

				pos.rotate(axis, angle);

				//	pos += barycenter;

				data.second.datas(i, 0) = pos[0];
				data.second.datas(i, 1) = pos[1];
				data.second.datas(i, 2) = pos[2];
			}

}

void Labeliser::clearCurves() {
	std::vector<std::tuple<std::string, vnl_matrix<double>>>outliers;

	for (auto& data : inputScene) {
		bool incomplete = false;
		::Vector3d lastNotNanPoint;
		::Vector3d lastLastNotNanPoint;
		unsigned int lastLastNotNanFrame = std::numeric_limits<unsigned int>::max();
		unsigned int lastNotNanFrame = std::numeric_limits<unsigned int>::max();

		for (unsigned int i = 0; i < data.second.datas.rows(); ++i) {
			const auto& point = ::Vector3d( {data.second.datas(i, 0), data.second.datas(i, 1), data.second.datas(i, 2)});

			double speed1 = std::numeric_limits<double>::max();
			unsigned int speed1Index = 0;

			if (!std::isnan(point[0])) {
				if (lastLastNotNanFrame != std::numeric_limits<unsigned int>::max()
						&& lastNotNanFrame != std::numeric_limits<unsigned int>::max()) {
					Vector3d speed1 = (point - lastNotNanPoint) * frameRate / (double) (i - lastNotNanFrame);
					Vector3d speed2 = (lastNotNanPoint - lastLastNotNanPoint) * frameRate / (double) (lastNotNanFrame - lastLastNotNanFrame);

					Vector3d acceleration = (speed1 - speed2) / 2.;

					if (acceleration.getNorm() > accelerationMax) {
						if (!incomplete)
						outliers.push_back(std::tuple<std::string, vnl_matrix<double>> {"outlier_" + std::to_string(outlierUUID.getUUID()),
									vnl_matrix<double>(data.second.datas.rows(), data.second.datas.cols(), std::nan(""))});

						std::get<1>(outliers.back())(lastNotNanFrame, 0) = data.second.datas(lastNotNanFrame, 0);
						std::get<1>(outliers.back())(lastNotNanFrame, 1) = data.second.datas(lastNotNanFrame, 1);
						std::get<1>(outliers.back())(lastNotNanFrame, 2) = data.second.datas(lastNotNanFrame, 2);

						data.second.datas(lastNotNanFrame, 0) = std::nan("");
						data.second.datas(lastNotNanFrame, 1) = std::nan("");
						data.second.datas(lastNotNanFrame, 2) = std::nan("");

						incomplete = true;
					}
				}

				lastLastNotNanFrame = lastNotNanFrame;
				lastNotNanFrame = i;

				lastLastNotNanPoint = lastNotNanPoint;
				lastNotNanPoint = point;
			}
		}
	}

	for (const auto& outlier : outliers)
	inputScene[std::get<0>(outlier)].datas = std::get<1>(outlier);

	updateIncompletePoints();
}

void Labeliser::updateIncompletePoints() {
	incompletePoints.clear();

	unsigned int lastFrame = 0;

	for (const auto& data : inputScene) {
		unsigned int gap = 0;
		try {
			::Vector3d lastNotNanPoint;
			::Vector3d lastLastNotNanPoint;
			unsigned int lastLastNotNanFrame = std::numeric_limits<unsigned int>::max();
			unsigned int lastNotNanFrame = std::numeric_limits<unsigned int>::max();

			for (unsigned int i = 0; i < data.second.datas.rows(); ++i) {
				if (std::isnan(data.second.datas(i, 0))) {
					++gap;

					if (gap > gapFramesSize)
						throw std::exception();
				} else {
					gap = 0;
					lastFrame = i;

					const auto& point = ::Vector3d( { data.second.datas(i, 0), data.second.datas(i, 1), data.second.datas(i, 2) });

					double speed1 = std::numeric_limits<double>::max();
					unsigned int speed1Index = 0;

					if (!std::isnan(point[0])) {
						if (lastLastNotNanFrame != std::numeric_limits<unsigned int>::max()
								&& lastNotNanFrame != std::numeric_limits<unsigned int>::max()) {
							Vector3d speed1 = (point - lastNotNanPoint) * frameRate / (double) (i - lastNotNanFrame);
							Vector3d speed2 = (lastNotNanPoint - lastLastNotNanPoint) * frameRate
									/ (double) (lastNotNanFrame - lastLastNotNanFrame);

							Vector3d acceleration = (speed1 - speed2) / 2.;

							if (acceleration.getNorm() > accelerationMax)
								throw std::exception();
						}

						lastLastNotNanFrame = lastNotNanFrame;
						lastNotNanFrame = i;

						lastLastNotNanPoint = lastNotNanPoint;
						lastNotNanPoint = point;
					}
				}
			}
		} catch (...) {
			incompletePoints[data.first] = lastFrame;
		}
	}
}

void Labeliser::getInputSceneDatas(vnl_matrix<double>& datas, std::vector<std::string>& labels,
		std::unordered_map<std::string, unsigned int>& incompletePoints) const {
	getInputDatas(currentFrame, datas, labels, inputScene);
	incompletePoints = this->incompletePoints;
}

void Labeliser::getInputSceneDatas(const std::string& label, vnl_matrix<double>& datas) const {
	datas = inputScene.at(label).datas;
}

void Labeliser::updateLabelisationBox(unsigned long long int boxIndex, const Vector3d& coords1, const Vector3d& coords2,
		const std::string& label) {
	try {
		auto& labBox = labelisationBoxes.at(boxIndex);

		std::get<0>(labBox) = label;

		auto& box = std::get<1>(labBox);

		box.setBeggin(coords1);
		box.setEnd(coords2);
	} catch (...) {
		labelisationBoxes.insert(std::unordered_map<unsigned long long int, std::tuple<std::string, labeliser::Box>>::value_type(boxIndex =
				labBoxUUID.getUUID(), std::tuple<std::string, labeliser::Box> { label, labeliser::Box(coords1, coords2) }));
	}
}

void Labeliser::removeLabelisationBox(unsigned long long int boxIndex) {
	labelisationBoxes.erase(boxIndex);
	labBoxUUID.freeUUID(boxIndex);
}

const std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>& Labeliser::getMarkerGroups(const std::string& label) const {
	return estimationSets.at(label);
}

void Labeliser::addMarkerGroup(const GroupMarker& group) {
	removeMarkerGroup(group.getUUID());
	auto& newGroup = groupMarkers[group.getUUID()] = std::make_shared<GroupMarker>(group);

	for (const auto& marker : group.getMarkers())
		estimationSets[std::get<0>(marker)][group.getUUID()] = newGroup;
}

void Labeliser::addMarkerToGroup(const std::string& label, unsigned long long int id) {
	try {
		getMarkerGroups(label).at(id);
		return;
	} catch (...) {
	}

	std::shared_ptr<GroupMarker> groupMarker = nullptr;

	for (const auto& groupIt : groupMarkers)
		if (groupIt.first == id) {
			groupMarker = groupIt.second;
			break;
		}

	if (groupMarker != nullptr)
		estimationSets.at(label)[id] = groupMarker;
	else
		std::cerr << "Error : error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
}

void Labeliser::removeMarkerFromGroup(const std::string& label, unsigned long long int id) {
	try {
		auto& set = estimationSets.at(label);
		auto& group = set.at(id);
		group->eraseMarker(label);

		set.erase(id);

		if (group->getMarkers().size() == 0)
			removeMarkerGroup(id);

	} catch (...) {
	}
}

void Labeliser::removeMarkerFromGroups(const std::string& label) {
	try {
		auto groups = getMarkerGroups(label);

		for (const auto& groupIt : groups)
			removeMarkerFromGroup(label, groupIt.first);
	} catch (...) {
	}
}

void Labeliser::removeMarkerGroup(unsigned long long int id) {
	try {
		auto& group = groupMarkers.at(id);

		for (const auto& marker : group->getMarkers())
			try {
				auto& set = estimationSets.at(std::get<0>(marker));
				set.erase(id);
			} catch (...) {
			}

		groupMarkers.erase(id);
	} catch (...) {
	}
}

void Labeliser::updateMarkerGroupsFrom(const std::string& label, std::unordered_map<unsigned long long int, GroupMarker>& groups) {
	try {	// si le marker contient déjà des groups (1)
		auto& set = estimationSets.at(label);

		std::vector<unsigned long long int> groupsEraser = std::vector<unsigned long long int>();

		// si un des groups de "set" n'est pas contenu dans "groups" -> le group à été supprimé => on supprime le group dans "set" pour le label "label"
		for (const auto& group : set)
			try {
				groups.at(group.first);
			} catch (...) {
				group.second->eraseMarker(label);
				groupsEraser.push_back(group.first);
			}

		for (const auto& group : groupsEraser)
			set.erase(group);

		// si un des des groups de "groups" n'est pas contenu dans "set" -> le group à été ajouté au marker => on ajoute le group dans "set" pour le label "label"
		for (const auto& group : groups)
			try {	//si le group est déjà lié au marker, on met à jour sa
				set.at(group.first)->setMarkerMargin(label, group.second.getMargin(label));
			} catch (...) {
				try {
					auto& g2 = set[group.first] = groupMarkers.at(group.first); // si le group éxiste déjà, on lit le marker à ce group
					g2->addMarker(label, group.second.getMargin(label));
				} catch (...) { // sinon error (group inexistant ...)
					std::cerr << "Error : error occured in file : " << __FILE__ << ", at line : " << __LINE__ << std::endl;
				}
			}
	} catch (...) { //(1) sinon
		auto& set = estimationSets[label];

		for (auto groupIt : groups) {
			auto& group = groupMarkers[groupIt.first];
			group->addMarker(label, groupIt.second.getMargin(label));
			set.insert(std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>::value_type(groupIt.first, group));
		}
	}
}

std::string Labeliser::getDefaultModelSettingsPath() const {
	auto tmp = modelFilePath.find_last_of(".");
	auto path = modelFilePath.substr(0, tmp) + ".settings";

	return path;
}

void Labeliser::saveModelSettingsToFile(HWND hwnd, const std::string& path) const {
	while (true)
		try {
			auto rootTag = utils::xml::Reader::read(path);
			auto boxes = rootTag->getOrCreateChild("boxes");
			rootTag->removeChild("groups");
			auto groups = rootTag->createChild("groups");
			auto labelisationBoxesTag = boxes->getOrCreateChild("labelisationBoxes");
			auto supressionBoxesTag = boxes->getOrCreateChild("supressionBoxes");

			labelisationBoxesTag->removeChilds("box");
			supressionBoxesTag->removeChilds("box");

			for (const auto& box : labelisationBoxes) {
				auto child = std::make_shared<utils::xml::Tag>();
				child->setName("box");
				child->addParam("x1", std::to_string(std::get<1>(box.second).getBeggin()[0]));
				child->addParam("y1", std::to_string(std::get<1>(box.second).getBeggin()[1]));
				child->addParam("z1", std::to_string(std::get<1>(box.second).getBeggin()[2]));
				child->addParam("x2", std::to_string(std::get<1>(box.second).getEnd()[0]));
				child->addParam("y2", std::to_string(std::get<1>(box.second).getEnd()[1]));
				child->addParam("z2", std::to_string(std::get<1>(box.second).getEnd()[2]));

				if (std::get<0>(box.second) == "outlier")
					supressionBoxesTag->addChild(child);
				else {
					child->addParam("label", std::get<0>(box.second));
					labelisationBoxesTag->addChild(child);
				}
			}

			std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>> groupMarkers = std::unordered_map<
					unsigned long long int, std::shared_ptr<GroupMarker>>();

			for (const auto& setIt : estimationSets)
				for (const auto& set : setIt.second) {
					if (std::find(groupMarkers.begin(), groupMarkers.end(), set) != groupMarkers.end())
						continue;

					auto setTag = groups->createChild("group");

					double margin = set.second->getGlobalMargin();

					setTag->addParam("margin", std::to_string(margin));

					for (const auto& marker : set.second->getMarkers()) {
						auto child = setTag->createChild("marker");

						child->addParam("label", std::get<0>(marker));

						if (std::get<1>(marker) != margin)
							child->addParam("margin", std::to_string(std::get<1>(marker)));
					}

					groupMarkers[set.first] = set.second;
				}

			utils::xml::Writter::write(path, rootTag);

			break;
		} catch (...) {
			if (MessageBox(hwnd, (SERIALIZER->getSaverErrorCore1() + path + SERIALIZER->getSaverErrorCore2()).c_str(), SERIALIZER->getSaverErrorTitle().c_str(),
			MB_YESNO) != IDYES)
			throw std::exception();
		}
	}

void Labeliser::saveToFile(const std::string& file, const std::shared_ptr<unsigned short>& loadingPercentage) const {
	std::vector<std::string> labels;

	for (const auto& label : inputScene)
		labels.push_back(label.first);

	auto it = inputScene.begin();

	utils::c3d::Writter::write(file, inputScene.size(), 0, getNbFrames() - 1, 0, 250.f, labels,
			[this, &it, loadingPercentage](float& x, float& y, float& z, uint32_t& res, unsigned int frame) {
				auto& marker = it->second.datas;

				if (std::isnan(marker(frame, 0))) {
					x = y = z = 0;
					res = 0xBF800000;
				} else {
					x = marker(frame, 0);
					y = marker(frame, 1);
					z = marker(frame, 2);

					res = 0;
				}

				++it;

				if (it == inputScene.end())
				it = inputScene.begin();

				*loadingPercentage = 100 * (frame + 1) / getNbFrames();
			});
}

void Labeliser::setModelFrame(unsigned int frame) {
	modelFrame = frame;

	inputModel.clear();

	for (const auto it : inputScene) {
		if (!(it.first.size() > 6 && it.first.substr(0, 7) == "outlier") && !std::isnan(it.second.datas(frame, 0))) {
			auto& data = inputModel[it.first].datas;
			data.set_size(1, 3);
			data(0, 0) = it.second.datas(frame, 0);
			data(0, 1) = it.second.datas(frame, 1);
			data(0, 2) = it.second.datas(frame, 2);
		}
	}

	setGapFrames();
}

unsigned int Labeliser::getModelFrame() const {
	return modelFrame;
}

void Labeliser::setCurrentFrame(unsigned int frame) {
	std::clog << ("[info][labeliser] go to \"" + std::to_string(frame) + "\"") << std::endl;
	this->currentFrame = frame;

	nbModelPoints = inputModel.size();
	nbScenePoints = 0;

	for (const auto& scene : inputScene)
		if (!std::isnan(scene.second.datas(frame, 0)) && scene.first.substr(0, 7) != "outlier")
			++nbScenePoints;

	setCurrentPredictionsPoints();
}

unsigned int Labeliser::getNbScenePoints() const {
	return nbScenePoints;
}

unsigned int Labeliser::getNbSceneMarkers() const {
	return inputScene.size();
}

unsigned int Labeliser::getNbModelPoints() const {
	return nbModelPoints;
}

unsigned int Labeliser::getNbFrames() const {
	return inputScene.begin()->second.datas.rows();
}

void Labeliser::setGapFrames() {
	gapframes.clear();
	for (const auto& scene : inputScene) {
		if (!std::isnan(scene.second.datas(0, 0))
				|| scene.first.substr(0, sceneLabelUnlabelisedPrefix.size()) != sceneLabelUnlabelisedPrefix)
			continue;

		for (unsigned int frameIt = 1; frameIt < scene.second.datas.rows(); ++frameIt)
			if (!std::isnan(scene.second.datas(frameIt, 0))) {
				gapframes[frameIt].push_back(scene.first);
				break;
			}
	}
}

const std::unordered_map<std::string, std::tuple<::Vector3d, double>>& Labeliser::getCurrentPredictionPoints() const {
	return estimationPoints;
}

void Labeliser::setCurrentPredictionsPoints() {
	estimationPoints.clear();

	for (const auto& point : estimationSets) {
		auto& it = estimationPoints[point.first];

		try {
			getPredictionCoords(std::get<0>(it), point.first, currentFrame, std::get<1>(it));
		} catch (...) {
			estimationPoints.erase(point.first);
			//todo exceptions
		}
	}
}

bool Labeliser::checkPredictionMatch(const std::string& label, const ::Vector3d& coords) const {
	::Vector3d predictedPoint;
	double margin;

	getPredictionCoords(predictedPoint, label, currentFrame, margin);

	return (predictedPoint - coords).getNorm() < margin;
}

void Labeliser::getPredictionRot(std::tuple<double, ::Vector3d>& rotation, const std::vector<std::tuple<::Vector3d, ::Vector3d>>& set,
		bool calculateAxis) const {

	auto& rotVec = std::get<1>(rotation);
	auto rotationMoy = ::Vector3d();

	if (calculateAxis) {
		rotVec = Vector3d::center;

		for (const auto& pair : set) {
			const auto& modelPoint = std::get<0>(pair);
			const auto& scenePoint = std::get<1>(pair);

			auto rotVec2 = modelPoint.getRotationWith(scenePoint);

			if (std::get<0>(rotVec2) == 0)
				continue;

			rotVec += std::get<1>(rotVec2) * (modelPoint - (modelPoint * std::get<1>(rotVec2)) * std::get<1>(rotVec2)).getNorm();
		}

		double r = rotVec.normalize();

		if (r == 0)
			throw std::exception(); // todo exception
	}

	for (const auto& pair : set) {
		const auto& modelPoint = std::get<0>(pair);
		const auto& scenePoint = std::get<1>(pair);

		::Vector3d axis1 = rotVec ^ (modelPoint.normalized() ^ rotVec);
		axis1.normalize();
		::Vector3d axis2 = rotVec ^ axis1;
		axis2.normalize();

		::Vector3d modelProj = (modelPoint * axis1) * axis1 + (modelPoint * axis2) * axis2;
		::Vector3d sceneProj = (scenePoint * axis1) * axis1 + (scenePoint * axis2) * axis2;
		double rot = std::get<0>(sceneProj.getRotationWith(modelProj));

		double norm = modelProj.getNorm();

		rotationMoy[0] += cos(rot) * norm;
		rotationMoy[1] += sin(rot) * norm;
	}

	rotationMoy.normalize();

	std::get<0>(rotation) = atan2(rotationMoy[1], rotationMoy[0]);

	if (rotationMoy[0] == rotationMoy[1] && rotationMoy[0] == 0)
		throw std::exception(); //todo exception
}

void Labeliser::getPredictionCoords(::Vector3d& predictedPoint, const std::string& label, unsigned int frame, double& margin) const {
	const auto& inputScene = this->inputScene;
	const auto& inputModel = this->inputModel;

	const auto& predictedPointModelIt = inputModel.find(label);

	if (predictedPointModelIt == inputModel.end())
		throw std::exception(); //todo exception

	const auto& predictedPointModel = predictedPointModelIt->second.datas;

	const auto& it = estimationSets.find(label);

	if (it == estimationSets.end())
		throw std::exception(); // todo exception

	margin = 0;

	for (const auto& set : it->second) {
		::Vector3d predictedPointIt;

		margin = std::max(set.second->getMargin(label), margin);

		::Vector3d modelBarycenter, sceneBarycenter;
		unsigned int nbDatas = 0;
		std::vector<std::tuple<::Vector3d, ::Vector3d>> matchingSet;

		//Calcul le barycentre du groups de marqueurs statiques
		for (const auto& pointIt : set.second->getMarkers()) {
			if (std::get<0>(pointIt) == label)
				continue;

			const auto& scenePoint = inputScene.find(std::get<0>(pointIt));
			if (scenePoint == inputScene.end() || std::isnan(scenePoint->second.datas(frame, 0)))
				continue;

			const auto& modelPoint = inputModel.find(std::get<0>(pointIt));
			if (modelPoint == inputModel.end())
				continue;

			::Vector3d model, scene;

			model[0] = modelPoint->second.datas(0, 0);
			model[1] = modelPoint->second.datas(0, 1);
			model[2] = modelPoint->second.datas(0, 2);
			modelBarycenter += model;

			scene[0] = scenePoint->second.datas(frame, 0);
			scene[1] = scenePoint->second.datas(frame, 1);
			scene[2] = scenePoint->second.datas(frame, 2);
			sceneBarycenter += scene;

			matchingSet.push_back(std::tuple<::Vector3d, ::Vector3d> { model, scene });
			++nbDatas;
		}

		if (nbDatas < 3)
			throw std::exception(); // todo exception

		modelBarycenter /= nbDatas;
		sceneBarycenter /= nbDatas;

		for (auto& pair : matchingSet) {
			std::get<0>(pair) -= modelBarycenter;
			std::get<1>(pair) -= sceneBarycenter;
		}

		std::tuple<double, ::Vector3d> rotation = std::tuple<double, ::Vector3d> { 0, ::Vector3d::xAxis };
		std::tuple<double, ::Vector3d> rotation2 = std::tuple<double, ::Vector3d> { 0, ::Vector3d::yAxis };

		try {
			//calcul du premier vecteur de rotation moyenné
			getPredictionRot(rotation, matchingSet);

			for (auto& point : matchingSet)
				std::get<0>(point).rotate(std::get<1>(rotation), std::get<0>(rotation));
		} catch (...) {
			rotation = std::tuple<double, ::Vector3d> { 0, ::Vector3d::xAxis };
		}

		try {
			//calcul du deuxième vecteur de rotation moyenné
			getPredictionRot(rotation2, matchingSet);
		} catch (...) {
			rotation2 = std::tuple<double, ::Vector3d> { 0, ::Vector3d::xAxis };
		}

		predictedPointIt[0] = predictedPointModel(0, 0) - modelBarycenter[0];
		predictedPointIt[1] = predictedPointModel(0, 1) - modelBarycenter[1];
		predictedPointIt[2] = predictedPointModel(0, 2) - modelBarycenter[2];

		predictedPointIt.rotate(std::get<1>(rotation), std::get<0>(rotation));
		predictedPointIt.rotate(std::get<1>(rotation2), std::get<0>(rotation2));

		predictedPointIt += sceneBarycenter;
		predictedPoint += predictedPointIt;
	}

	predictedPoint /= it->second.size();
}

void Labeliser::frameLabelisation() {
	auto& inputModel = this->inputModel;
	auto scene = vnl_matrix<double>(0, 0);
	auto model = vnl_matrix<double>(0, 0);
	auto modelLabels = std::unordered_map<unsigned int, std::string>();
	auto sceneLabels = std::unordered_map<unsigned int, std::string>();
	auto PInit = vnl_matrix<double>();
	auto frameCorrespondance = std::unordered_map<unsigned int, std::string>();
	unsigned int modelFrame = this->modelFrame == std::numeric_limits<unsigned int>::max() ? 0 : this->modelFrame;

	{
		vnl_matrix<double> datas(inputModel.size(), 3);
		unsigned int i = 0;

		for (const auto& data : inputModel) {
			if (data.first.substr(0, 8) == "outlier_")
				continue;

			datas(i, 0) = data.second.datas(0, 0);
			datas(i, 1) = data.second.datas(0, 1);
			datas(i, 2) = data.second.datas(0, 2);
			modelLabels[i] = data.first;

			frameCorrespondance[i] = data.first;

			++i;
		}

		model.set_size(i, 3);

		for (unsigned int j = 0; j < i; ++j) {
			model(j, 0) = datas(j, 0);
			model(j, 1) = datas(j, 1);
			model(j, 2) = datas(j, 2);
		}
	}

	{
		vnl_matrix<double> PInitTmp(model.rows(), inputScene.size(), 0.0);
		std::unordered_map<unsigned int, unsigned int> boxLabelised = std::unordered_map<unsigned int, unsigned int>();

		{
			vnl_matrix<double> datas(inputScene.size(), 3);
			unsigned int i = 0;

			for (const auto& data : inputScene) {
				if (data.first.substr(0, 8) == "outlier_" || std::isnan(data.second.datas(currentFrame, 0.0)))
					continue;

				datas(i, 0) = data.second.datas(currentFrame, 0);
				datas(i, 1) = data.second.datas(currentFrame, 1);
				datas(i, 2) = data.second.datas(currentFrame, 2);
				sceneLabels[i] = data.first;

				if (data.first.substr(0, sceneLabelUnlabelisedPrefix.size()) == sceneLabelUnlabelisedPrefix) {
					bool contained = false;

					for (const auto& box : labelisationBoxes)
						if (std::get<1>(box.second).isInside(
								Vector3d(
										{ data.second.datas(currentFrame, 0), data.second.datas(currentFrame, 1), data.second.datas(
												currentFrame, 2) }))) {
							if (std::get<0>(box.second) == "outlier") {
								--i;
								contained = true;
								break;
							}

							for (unsigned int j = 0; j < PInitTmp.rows(); ++j)
								if (frameCorrespondance[j] == std::get<0>(box.second)) {
									PInitTmp(j, i) = 1.0;

									try {
										boxLabelised.at(j);
										PInitTmp(j, i) = 0.0;
									} catch (...) {
										boxLabelised[j] = i;
									}
									break;
								}

							contained = true;
							break;
						}

					if (!contained)
						for (unsigned int j = 0; j < PInitTmp.rows(); ++j)
							PInitTmp(j, i) = -1.0;
				} else
					for (unsigned int j = 0; j < PInitTmp.rows(); ++j)
						if (frameCorrespondance[j] == data.first) {
							try {
								unsigned int ind = boxLabelised.at(j);
								PInitTmp(j, ind) = 0.0;
							} catch (...) {
							}

							boxLabelised[j] = i;
							PInitTmp(j, i) = 1.0;
							break;
						}
				++i;
			}

			scene.set_size(i, 3);

			PInit.set_size(PInitTmp.rows(), i);

			for (unsigned int j = 0; j < i; ++j) {

				for (unsigned int k = 0; k < PInit.rows(); ++k)
					PInit(k, j) = PInitTmp(k, j);

				scene(j, 0) = datas(j, 0);
				scene(j, 1) = datas(j, 1);
				scene(j, 2) = datas(j, 2);
			}
		}
	}

	gmmreg::CoherentPointDriftGrbf cpd;

	cpd.setInitP(PInit);
	if (scene.rows() > 0)
		cpd.Run(".//labelisation.ini", scene, model);

	std::vector<std::string> identicLabels;

	const vnl_matrix<double>& P = cpd.getP();

	std::shared_ptr<window::observable::LabellisationEndedEvent> event = std::make_shared<window::observable::LabellisationEndedEvent>();

	{
		std::unordered_map<unsigned int, std::unordered_map<unsigned int, bool>> arePointsLinked = std::unordered_map<unsigned int,
				std::unordered_map<unsigned int, bool>>();
		std::unordered_map<unsigned int, bool> isModelPointLinked = std::unordered_map<unsigned int, bool>();

		// Recherche du point du model correspondant pour chacuns des points de la scene (recherche de la meilleur probabilité)
		for (unsigned int j = 0; j < P.cols(); ++j) {
			float pmax = 0.f;
			unsigned int index = std::numeric_limits<unsigned int>::max();

			for (unsigned int i = 0; i < P.rows(); ++i) {
				if (PInit(i, j) == 1.0) {
					// point déjà lié dans une labélisation précédante
					// => c'est le point correspondant
					index = i;
					pmax = std::numeric_limits<float>::max();						// toutes les autres correspondances sont abbérantes
				} else if (P(i, j) > pmax) { // Ce point à une meilleure correspondance que les précédants
					pmax = P(i, j);
					index = i;
				}

				arePointsLinked[i][j] = false; // initialisation de la matrice
			}

			if (index != std::numeric_limits<unsigned int>::max()) { // Définition du point modèle qui correspond au mieux a ce point
				arePointsLinked[index][j] = true;
				isModelPointLinked[index] = true;
			}
		}

		// à ce stade, pour chaques points de la scène, on à trouvé un point du modèle correspondant
		// Il faut maintenant supprimmer les liaisons multiples entre un point du modèle et plusieurs points de la scene

		std::vector<unsigned int> unlinkedPoints = std::vector<unsigned int>();

		//pour chaque points du modèle, on check les points de la scène correspondant afin de n'en retenir qu'un seul
		for (unsigned int i = 0; i < P.rows(); ++i) {
			float pmax = 0.f;
			unsigned int lastIndex = std::numeric_limits<unsigned int>::max();

			for (unsigned int j = 0; j < P.cols(); ++j)
				if (arePointsLinked[i][j])
					if (lastIndex != std::numeric_limits<unsigned int>::max()) {
						if (P(i, j) > pmax || PInit(i, j) == 1.0) {
							if (PInit(i, j) == 1.0)
								// PInit(i, j) == 1.0 : point déjà lié dans une labélisation précédante
								// => c'est le point correspondant
								pmax = std::numeric_limits<float>::max();
							else
								pmax = P(i, j);

							arePointsLinked[i][lastIndex] = false;						// le point de la scène de proba inf est délié
							unlinkedPoints.push_back(lastIndex);					// on l'enregistre afin de lui trouver un autre copin
							lastIndex = j;
						} else { // le point à une proba inf à un des points prec => on le délie
							arePointsLinked[i][j] = false;
							unlinkedPoints.push_back(j); // on l'enregistre afin de lui trouver un autre copin
						}
					} else {
						// initialisation
						lastIndex = j;
						pmax = P(i, j);
					}
		}

		bool changesApplied = true;

		while (changesApplied) { // on continue tant que des changement sont possibles
			changesApplied = false;
			std::vector<unsigned int> unlinkedPoints2 = std::vector<unsigned int>();

			// pour tous les points de la scène qui ont été délié on recherche un nouveau point du modèle
			// qui n'est lié à aucuns points et dont la proba de correspondance est la meilleur
			for (auto j : unlinkedPoints) {
				unsigned int index = std::numeric_limits<unsigned int>::max();
				float pmax = 0.f;

				for (unsigned int i = 0; i < P.rows(); ++i)
					if (isModelPointLinked.find(i) == isModelPointLinked.end() && P(i, j) > pmax) {
						// le point du modèle n'est lié à aucuns points et la proba est meilleur qu'une des précédante
						index = i;
						pmax = P(i, j);
					}

				if (index != std::numeric_limits<unsigned int>::max()) {
					arePointsLinked[index][j] = true;
					isModelPointLinked[index] = true;
					changesApplied = true;
				} else
					unlinkedPoints2.push_back(j);
			}

			unlinkedPoints = unlinkedPoints2;
		}

		// les correspondances étant maintenant établie, on peut créer le résultat de sortie

		for (unsigned int i = 0; i < scene.rows(); ++i) {
			bool linked = false;
			const auto& sceneName = sceneLabels[i];

			if (sceneName.size() < sceneLabelUnlabelisedPrefix.size()
					|| sceneName.substr(0, sceneLabelUnlabelisedPrefix.size()) != sceneLabelUnlabelisedPrefix) {
				continue;
			}

			for (unsigned int j = 0; j < model.rows(); ++j)
				if (arePointsLinked[j][i]) {
					linked = true;

					if (this->modelFrame == std::numeric_limits<unsigned int>::max() || P(j, i) > 0.4) {
						event->addCorrespondance(sceneName, modelLabels[j], P(j, i));
					} else
						linked = false;
				}

			if (!linked)
				event->addCorrespondance(sceneName, "outlier", 0);
		}
	}

	notify(event);
}

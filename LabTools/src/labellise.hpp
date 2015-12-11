/*
 * labelise.hpp
 *
 *  Created on: 26 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_LABELLISE_HPP_
#define SRC_LABELLISE_HPP_

#include <vnl/vnl_matrix.h>
#include <windef.h>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "datas/Box.h"
#include "datas/DataStruct.h"
#include "GroupMarker.h"
#include "utils/math/Vector.h"
#include "utils/observable/Observable.h"
#include "utils/UUID.h"

namespace window {
namespace observable {
class Event;
} /* namespace observable */
} /* namespace window */

class Labeliser: public Observable<const std::shared_ptr<window::observable::Event>&> {
public:
	virtual ~Labeliser();
	Labeliser(std::unordered_map<std::string, generic::DataStruct>& inputModel,
			std::unordered_map<std::string, generic::DataStruct>& inputScene,
			const std::unordered_map<std::string, std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>>& estimationSets, const std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>& groupMarkers,
			std::vector<std::tuple<std::string, labeliser::Box>>& labelisationBoxes, unsigned int gapFramesSize, double accelerationMax, double frameRate, const std::string& modelFilePath);

			static void run(std::unordered_map<std::string, generic::DataStruct>& inputModel,
			std::unordered_map<std::string, generic::DataStruct>& inputScene,
			const std::unordered_map<std::string, std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>>& estimationSets, const std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>& groupMarkers,
			std::vector<std::tuple<std::string, labeliser::Box>>& labelisationBoxes, unsigned int gapFramesSize, const std::string& sceneFilePath, const std::string& modelFilePath, double probaMin, double accelerationMax, double frameRate);

			void frameLabelisation();
			const std::unordered_map<unsigned long long int, std::tuple<std::string, labeliser::Box>>& getLabelisationBoxes() const;
			unsigned int getNextLostPointFrame() const;
			const std::vector<std::string>& getNextLostPointLabels(unsigned int frame) const;
			unsigned int getPreviousLostPointFrame() const;
			bool isGapFrame() const;
			unsigned int getNbGapFrames() const;
			const std::vector<std::string>& getPreviousLostPointLabels(unsigned int frame) const;
			void renameLabel(const std::string& oldLabel, const std::string& newLabel);
			void splitLabel(const std::string& label, unsigned int begginFrame, unsigned int endFrame);
			void erasePoint(const std::string& name);
			void getInputModelDatas(vnl_matrix<double>& datas, std::vector<std::string>& labels) const;
			void getInputSceneDatas(vnl_matrix<double>& datas, std::vector<std::string>& labels, std::unordered_map<std::string, unsigned int>& incompletePoints) const;
			void getInputSceneDatas(const std::string& label, vnl_matrix<double>& datas) const;
			void setCurrentFrame(unsigned int frame);
			void setModelFrame(unsigned int frame);
			unsigned int getModelFrame() const;
			unsigned int getNbSceneMarkers() const;
			unsigned int getNbScenePoints() const;
			unsigned int getNbModelPoints() const;
			unsigned int getNbFrames() const;
			void setGapFrames();
			void getPredictionCoords(::Vector3d& predictedPoint, const std::string& label, unsigned int frame, double& margin) const;
			void getPredictionRot(std::tuple<double, ::Vector3d>& rot, const std::vector<std::tuple<::Vector3d, ::Vector3d>>& set, bool calculateAxis = true) const;
			void setCurrentPredictionsPoints();
			const std::unordered_map<std::string, std::tuple<::Vector3d, double>>& getCurrentPredictionPoints() const;
			bool checkPredictionMatch(const std::string& label, const ::Vector3d& coords) const;
			void saveToFile(const std::string& path, const std::shared_ptr<unsigned short>&) const;
			void saveModelSettingsToFile(HWND, const std::string&) const;
			std::string getDefaultModelSettingsPath() const;
			void updateLabelisationBox(unsigned long long int index, const Vector3d& coords1, const Vector3d& coords2, const std::string& label);
			void removeLabelisationBox(unsigned long long int index);
			const std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>& getMarkerGroups(const std::string& label) const;
			void addMarkerGroup(const GroupMarker&);
			void addMarkerToGroup(const std::string& label, unsigned long long int id);
			void removeMarkerFromGroup(const std::string& label, unsigned long long int id);
			void removeMarkerFromGroups(const std::string& label);
			void removeMarkerGroup(unsigned long long int id);
			void updateMarkerGroupsFrom(const std::string& label, std::unordered_map<unsigned long long int, GroupMarker>& groups);
			void updateIncompletePoints();
			void clearCurves();
			const utils::UUID& getLabelisationBoxesUUID () const;
			void rotateDatas(const ::Vector3d& axis, double angle);

		private:
			std::unordered_map<std::string, generic::DataStruct> inputModel;
			std::unordered_map<std::string, generic::DataStruct>& inputScene;
			std::unordered_map<std::string, unsigned int> incompletePoints = std::unordered_map<std::string, unsigned int>();
			std::map<unsigned int, std::vector<std::string>> gapframes;
			std::unordered_map<std::string, std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>> estimationSets;
			std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>> groupMarkers;
			std::unordered_map<std::string, std::tuple<::Vector3d, double>> estimationPoints;
			std::vector<unsigned int> offPositionFrames;
			unsigned int modelFrame = std::numeric_limits<unsigned int>::max();
			unsigned int currentFrame = 0;
			unsigned int nbScenePoints = 0;
			unsigned int nbModelPoints = 0;
			static constexpr unsigned int minOffPositionNbFrames = 100;
			static constexpr float maxOffPositionDelta2 = 1e-10;
			std::unordered_map<unsigned long long int, std::tuple<std::string, labeliser::Box>> labelisationBoxes;
			utils::UUID outlierUUID = utils::UUID();
			utils::UUID labBoxUUID = utils::UUID();
			std::string modelFilePath;
			unsigned int gapFramesSize;
			double frameRate;
			double accelerationMax;

			void getInputDatas(unsigned int frame, vnl_matrix<double>& datas, std::vector<std::string>& labels,
			const std::unordered_map<std::string, generic::DataStruct>& input) const;
		};

#endif /* SRC_LABELLISE_HPP_ */

/*
 * Window.h
 *
 *  Created on: 30 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_WINDOW_WINDOW_H_
#define SRC_WINDOW_WINDOW_H_

#include <vxl/core/vnl/vnl_matrix.h>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <thread>
#include <stack>
#include <windows.h>

#include "../labellise.hpp"
#include "../utils/observable/Observable.h"
#include "../utils/observable/Observer.h"
#include "../Controller/Controller.h"
#include "../Editor/Editor.h"
#include "../labeliserMenu/LabeliserMenu.h"
#include "../labeliserMenu/Validator.h"
#include "Layer/content/plot/point/Selector.h"
#include "Layer/content/plot/point/ScenePoint.h"
#include "Layer/content/plot/point/ModelPoint.h"
#include "Layer/content/plot/point/SpherePoint.h"
#include "Layer/content/plot/box/ResizableBox.h"

namespace sf {
class Color;
class RenderWindow;
} /* namespace sf */
namespace std {
class thread;
} /* namespace std */
namespace utils {
class Line;
class ScenePoint;
class Point;
class Box;
} /* namespace utils */
namespace window {
class Button;
class CenteredLayer;
class ConstrainedLayer;
class Plot3d;
class Plot2d;
class SplitLayer;
class StakeLayer;
class WindowLayer;
namespace observable {
class Event;
} /* namespace observable */
} /* namespace window */

class Labeliser;

namespace window {

class Window: public Observer<const std::shared_ptr<window::observable::Event>&> {
public:
	struct LabeliseAccessorTypes {
		typedef void (Labeliser::*SaveToFile)(const std::string& path, const std::shared_ptr<unsigned short>&) const;
		typedef void (Labeliser::*SaveModelSettingsToFile)(HWND, const std::string& path) const;
		typedef std::string (Labeliser::*GetDefaultModelSettingsPath)() const;
		typedef unsigned int (Labeliser::*GetNbSceneMarkers)() const;
		typedef unsigned int (Labeliser::*GetNbFrames)() const;
		typedef const utils::UUID& (Labeliser::*GetLabelisationBoxesUUID)() const;
		typedef void (Labeliser::*GetInputModelDatas)(vnl_matrix<double>&, std::vector<std::string>&) const;
		typedef void (Labeliser::*GetInputSceneDatas)(vnl_matrix<double>&, std::vector<std::string>&,
				std::unordered_map<std::string, unsigned int>&) const;
		typedef void (Labeliser::*GetInputSceneDatas2)(const std::string&, vnl_matrix<double>&) const;
		typedef void (Labeliser::*ErasePoint)(const std::string&);
		typedef void (Labeliser::*RenameLabel)(const std::string&, const std::string&);
		typedef unsigned int (Labeliser::*GetLostPointFrame)() const;
		typedef unsigned int (Labeliser::*GetCoherentLostPointFrame)() const;
		typedef unsigned int (Labeliser::*GetNbPoints)() const;
		typedef unsigned int (Labeliser::*GetNbGapFrames)() const;
		typedef void (Labeliser::*SetCurrentFrame)(unsigned int);
		typedef void (Labeliser::*SetModelFrame)(unsigned int);
		typedef void (Labeliser::*SetGapFrames)();
		typedef void (Labeliser::*UpdateIncompletePoints)();
		typedef bool (Labeliser::*IsGapFrame)() const;
		typedef void (Labeliser::*FrameLabelisation)();
		typedef bool (Labeliser::*CheckPredictionMatch)(const std::string&, const ::Vector3d&) const;
		typedef const std::unordered_map<std::string, std::tuple<::Vector3d, double>>& (Labeliser::*GetCurrentPredictionPoints)() const;
		typedef const std::unordered_map<unsigned long long int, std::shared_ptr<GroupMarker>>& (Labeliser::*GetMarkerGroups)(
				const std::string& label) const;
		typedef void (Labeliser::*AddMarkerGroup)(const GroupMarker& group);
		typedef void (Labeliser::*AddMarkerToGroup)(const std::string& label, unsigned long long int groupId);
		typedef void (Labeliser::*RemoveMarkerFromGroup)(const std::string& label, unsigned long long int groupId);
		typedef void (Labeliser::*RemoveMarkerGroup)(unsigned long long int groupId);
		typedef void (Labeliser::*RemoveMarkerFromGroups)(const std::string& label);
		typedef const std::unordered_map<unsigned long long int, std::tuple<std::string, labeliser::Box>>&(Labeliser::*GetLabelisationBoxes)() const;
		typedef void (Labeliser::*UpdateLabelisationBox)(unsigned long long int index, const Vector3d& coords1, const Vector3d& coords2,
				const std::string& label);
		typedef void (Labeliser::*RemoveLabelisationBox)(unsigned long long int index);
		typedef void (Labeliser::*UpdateMarkerGroupsFrom)(const std::string& label,
				std::unordered_map<unsigned long long int, GroupMarker>& groups);
		typedef void (Labeliser::*ClearCurves)();
		typedef void (Labeliser::*RotateDatas)(const ::Vector3d& axis, double angle);
	};

	template<typename >
	class LabeliseAccessor;

	template<typename Return, typename ... Params>
	class LabeliseAccessor<Return (Labeliser::*)(Params...)> {
	public:
		static Return access(Window& labeliser, Return (Labeliser::*memberPtr)(Params...), Params ...params);
	};

	template<typename Return, typename ... Params>
	class LabeliseAccessor<Return (Labeliser::*)(Params...) const> {
	public:
		static Return access(Window& labeliser, Return (Labeliser::*memberPtr)(Params...) const, Params ...params);
	};

	virtual ~Window();

	void run(const std::string sceneFilePath);
	unsigned int getHeight() const;
	void setHeight(unsigned int height = 600);
	unsigned int getWidth() const;
	void setWidth(unsigned int width = 800);
	void initializePlot(bool withMatches = true);
	void addPointToPlot(const std::shared_ptr<utils::Point>& point);
	void addBoxToPlot(const std::shared_ptr<utils::Box>& box, unsigned long long int index);
	void addLineToPlot(const std::shared_ptr<utils::Line>& line);
	std::shared_ptr<Plot3d> get3dPlotLayer();
	std::shared_ptr<Plot2d> get2dXPlotLayer();
	std::shared_ptr<Plot2d> get2dYPlotLayer();
	std::shared_ptr<Plot2d> get2dZPlotLayer();
	std::shared_ptr<SplitLayer> getSplitPlotLayer();
	//void setCurrentPlot(int frame);
	void clearPlot();
	std::shared_ptr<window::WindowLayer>& getFirstLayer();
	const std::vector<std::shared_ptr<utils::ModelPoint> >& getModelPoints() const;
	const std::vector<std::shared_ptr<utils::ScenePoint> >& getScenePoints() const;
	const std::vector<std::shared_ptr<utils::SpherePoint> >& getPredictionSpherePoints() const;
	const std::vector<std::shared_ptr<utils::Box> >& getLabelisationBoxes() const;
	const std::shared_ptr<point::Selector>& getSelector() const;
	void labeliserThreadAccessor(const std::function<void(const std::shared_ptr<Labeliser>&)>& thread);
	const std::shared_ptr<Controller>& getController() const;
	const std::shared_ptr<Editor>& getEditor() const;
	const std::shared_ptr<Validator>& getValidator() const;
	const std::shared_ptr<LabeliserMenu>& getLabeliserMenu() const;
	void attachThread(const std::shared_ptr<std::thread>& thread);
	void dettachThread(std::thread::id threadId);
	void displayModelPoint();
	void hideModelPoint();
	void hidePredictionSpherePoints();
	void displayPredictionSpherePoints();
	void hideLabelisationBoxes();
	void displayLabelisationBoxes();
	void hideMarkerGroups();
	void displayMarkerGroups();
	bool isMarkerGroupsDisplayed() const;
	void hideLabels();
	void displayLabels();
	bool isLabelsDisplayed() const;
	HWND getSystemHandle() const;
	void notifyModelSettingsChanged();
	unsigned int getGapFramesSizeMin() const;
	double getAccelerationMaxErrors() const;
	double getFrameRate() const;

	/**
	 * labelliserLock should be locked
	 */
	void update(Observable<const std::shared_ptr<window::observable::Event>&>& observable,
			const std::shared_ptr<window::observable::Event>& arg) override;

	Window(const std::shared_ptr<Labeliser>& labelliser, unsigned int nbFrames, double probaMin, unsigned int gapFramesSizeMin,
			double accelerationMax, double frameRate, unsigned int minWidth = 400, unsigned int minHeight = 400, unsigned int width = 800,
			unsigned int height = 600);

	static constexpr float pannelWidth = 200.f;
	static constexpr float mouseMenuWidth = 400.f;
	static sf::Color sceneColor;
	static sf::Color incompletePointColor;
	static sf::Color outlierColor;
	static sf::Color labellisedColor;
	static sf::Color labelisationBoxColor;
	static sf::Color errorPoint;
	static sf::Color selectedPoint;
	static sf::Color newlyLabellisedLinkColor;
	static sf::Color oldLabellisedLinkColor;
	static sf::Color modelColor;
	static sf::Color predictionSphereColor;
	static sf::Color newlySuppressedColorPoint;
	static sf::Color splitedColorPoint;
	static sf::Color selectColorPoint;
	static sf::Color selectColorLine;
	static sf::Color labelisedColorLine;
	static sf::Color lowProbaLinkColor;
	static sf::Color supressionBoxColor;
	static float suppressedSize;
	static float labellisedSize;
	static float pointSize;
	std::mutex windowLock;
	std::mutex labeliserLock;
	std::mutex labeliserMemberLock;
	unsigned int gapFramesSizeMin;
	double accelerationMax;
	double frameRate;

private:
	std::shared_ptr<WindowLayer> layer = nullptr;
	std::shared_ptr<Plot3d> plot3d = nullptr;
	std::shared_ptr<Plot2d> plot2dX = nullptr;
	std::shared_ptr<Plot2d> plot2dY = nullptr;
	std::shared_ptr<Plot2d> plot2dZ = nullptr;
	unsigned int width = 800;
	unsigned int height = 600;
	unsigned int minWidth = 400;
	unsigned int minHeight = 400;
	std::vector<std::shared_ptr<utils::ModelPoint>> modelPoints = std::vector<std::shared_ptr<utils::ModelPoint>>();
	std::vector<std::shared_ptr<utils::ScenePoint>> scenePoints = std::vector<std::shared_ptr<utils::ScenePoint>>();
	std::vector<std::shared_ptr<utils::SpherePoint>> predictionSpherePoints = std::vector<std::shared_ptr<utils::SpherePoint>>();
	std::vector<std::shared_ptr<utils::Box>> labelisationBoxes = std::vector<std::shared_ptr<utils::Box>>();
	std::shared_ptr<window::SplitLayer> splitLayerPlot = nullptr;
	std::shared_ptr<point::Selector> selector = nullptr;
	std::shared_ptr<Labeliser> labeliser;
	std::shared_ptr<Controller> controller = nullptr;
	std::shared_ptr<Validator> validator = nullptr;
	std::shared_ptr<LabeliserMenu> labeliserMenu = nullptr;
	std::shared_ptr<Editor> editor = nullptr;
	unsigned int nbModelPoints = 0;
	unsigned int nbScenePoints = 0;
	std::unordered_map<std::thread::id, std::shared_ptr<std::thread>> threads = std::unordered_map<std::thread::id,
			std::shared_ptr<std::thread>>();
	std::stack<std::thread::id> endedThreads = std::stack<std::thread::id>();
	bool displayModelPointFlag = true;
	bool displayPredictionSpheresFlag = false;
	bool displayLegendFlag = false;
	bool displayLabelsFlag = true;
	bool displayLabelisationBoxesFlag = false;
	bool displayMarkerGroupsFlag = false;
	std::shared_ptr<sf::RenderWindow> window = nullptr;
	bool modelSettingsChanged = false;
	utils::UUID labBoxUUID = utils::UUID();
	double probaMin = 0.98;

	inline void createTopMenu(std::shared_ptr<SplitLayer>& splitLayerBottom, std::shared_ptr<SplitLayer>& splitLayerTopMenu,
			unsigned int nbFrames, const std::shared_ptr<Button>& validate, const std::shared_ptr<Button>& cancel);
	inline void createBottomMenu(std::shared_ptr<SplitLayer>& splitLayerBottom, const std::shared_ptr<window::SplitLayer>& splitLayerPlot,
			std::shared_ptr<Button>& validate, std::shared_ptr<Button>& cancel);
	inline void createPlot();
	void createLabelisationBox(const std::shared_ptr<Button>& showLabelisationBoxes);
	void rotateDatas();
	void renameLabelisationBox(utils::ResizableBox& box);
	inline void createRightPannel(std::shared_ptr<window::SplitLayer>& splitLayerPlot);
	void setMatches();
	void deleteEndedThreads();
	std::shared_ptr<Labeliser> getLabeliser() const;
};

}
/* namespace window */

#endif /* SRC_WINDOW_WINDOW_H_ */

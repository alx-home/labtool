/*
 * Language.h
 *
 *  Created on: 6 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_LANGUAGE_LANGUAGE_H_
#define SRC_LANGUAGE_LANGUAGE_H_

#include <string>

namespace utils {
namespace language {

class Language {
public:
	virtual ~Language();

	virtual const std::string& getFirstLabelisationText() const = 0;
	virtual const std::string& getLabelisationText() const = 0;
	virtual const std::string& getValidationFirstLabelisationText() const = 0;
	virtual const std::string& getValidationLabelisationText() const = 0;
	virtual const std::string& getAutoModeText() const = 0;
	virtual const std::string& getEditText() const = 0;
	virtual const std::string& getAutoModeEndedText() const = 0;
	virtual const std::string& getAutoModeWaitText() const = 0;
	virtual const std::string& getEmptyCurvesButtonText() const = 0;

	/*C3DREADER_LANGUAGE_HEADERS*/

	virtual const std::string& getNumberOfMarker() const = 0;
	virtual const std::string& getNumberOfFrame() const = 0;
	virtual const std::string& getFirstFrameNbr() const = 0;
	virtual const std::string& getLastFrameNbr() const = 0;
	virtual const std::string& getScaleFactor() const = 0;
	virtual const std::string& getInvalidDataFormat() const = 0;
	virtual const std::string& getAnalogueDatasNotImplemented() const = 0;
	virtual const std::string& getAquisitionFrequency() const = 0;
	virtual const std::string& getProcessorUsed() const = 0;
	virtual const std::string& getInvalidProcessorType() const = 0;
	virtual const std::string& getParameterLabelsNotFound() const = 0;
	virtual const std::string& getEntityGroupNotFound1() const = 0;
	virtual const std::string& getEntityGroupNotFound2() const = 0;
	virtual const std::string& getInvalidTypeOrNumberOf3DPoints() const = 0;
	virtual const std::string& getFrameReading1() const = 0;
	virtual const std::string& getFrameReading2() const = 0;
	virtual const std::string& getC3dIntegerDatasNotImplemented() const = 0;
	virtual const std::string& getInvalidParameterType1() const = 0;
	virtual const std::string& getInvalidParameterType2() const = 0;
	virtual const std::string& getCharacterType() const = 0;
	virtual const std::string& getIntegerType() const = 0;
	virtual const std::string& getFloatType() const = 0;
	virtual const std::string& getByteType() const = 0;
	virtual const std::string& getModelPrefixSizeError1() const = 0;
	virtual const std::string& getModelPrefixSizeError2() const = 0;
	virtual const std::string& getScenePrefixSizeError1() const = 0;
	virtual const std::string& getScenePrefixSizeError2() const = 0;
	virtual const std::string& getParameterChildOverflowException1() const = 0;
	virtual const std::string& getParameterChildOverflowException2() const = 0;
	virtual const std::string& getParameterChildOverflowException3() const = 0;
	virtual const std::string& getParameterChildOverflowException4() const = 0;

	/*CONTROLLER_LANGUAGE_HEADERS*/

	virtual const std::string& getFrameNbr() const = 0;
	virtual const std::string& getNbPoints() const = 0;

	/*MEX_LANGUAGE_HEADERS*/

	virtual const std::string& getUsage1() const = 0;
	virtual const std::string& getUsage2() const = 0;

	/*EDITOR_LANGUAGE_HEADERS*/

	virtual const std::string& getSplitFrames() const = 0;
	virtual const std::string& getSplitAllFrames() const = 0;
	virtual const std::string& getSplitNextFrames() const = 0;
	virtual const std::string& getSplitPreviousFrames() const = 0;
	virtual const std::string& getLinkSupression() const = 0;
	virtual const std::string& getMarkerRename() const = 0;
	virtual const std::string& getAddMarkersToGroups() const = 0;
	virtual const std::string& getRemoveMarkersFromGroups() const = 0;
	virtual const std::string& getRemoveMarkerGroups() const = 0;
	virtual const std::string& getCreateGroupFromMarkers() const = 0;
	virtual const std::string& getSetGroupMargin() const = 0;
	virtual const std::string& getLinkMarkers() const = 0;

	/*LABELISER_MENU_LANGUAGE_HEADERS*/

	virtual const std::string& getAutoButtonText() const = 0;
	virtual const std::string& getValidateButtonText() const = 0;
	virtual const std::string& getCancelButtonText() const = 0;
	virtual const std::string& getStopButtonText() const = 0;
	virtual const std::string& getFirstLabelisationButtonText() const = 0;
	virtual const std::string& getLabeliseButtonText() const = 0;

	/*MESSAGES_BOX_LANGUAGE_HEADERS*/

	virtual const std::string& getLabelisationNotEndedCore() const = 0;
	virtual const std::string& getLabelisationNotEndedTitle() const = 0;
	virtual const std::string& getSaveBeforeExitCore() const = 0;
	virtual const std::string& getSaveBeforeExitTitle() const = 0;
	virtual const std::string& getSaverErrorCore1() const = 0;
	virtual const std::string& getSaverErrorCore2() const = 0;
	virtual const std::string& getSaverErrorTitle() const = 0;

	/*PLOT_MOUSE_MENU_LANGUAGE_HEADERS*/

	virtual const std::string& getShowModelPointText() const = 0;
	virtual const std::string& getShowPredictionSpheresText() const = 0;
	virtual const std::string& getHidePredictionSpheresText() const = 0;
	virtual const std::string& getHideModelPointsText() const = 0;
	virtual const std::string& getShowLegendText() const = 0;
	virtual const std::string& getShowLabelsText() const = 0;
	virtual const std::string& getHideLabelsText() const = 0;
	virtual const std::string& getHideLegendText() const = 0;
	virtual const std::string& getShowLabelisationBoxesText() const = 0;
	virtual const std::string& getHideLabelisationBoxesText() const = 0;
	virtual const std::string& getAddSuppressionBoxesText() const = 0;
	virtual const std::string& getAddLabelisationBoxesText() const = 0;
	virtual const std::string& getShowGroupsText() const = 0;
	virtual const std::string& getHideGroupsText() const = 0;
	virtual const std::string& getRotateDatasText() const = 0;

	/*SPLASHSCREEN_SAVER_LANGUAGE_HEADERS*/

	virtual const std::string& getOuputFileSelectText() const = 0;
	virtual const std::string& getSaveSettingsFile() const = 0;
	virtual const std::string& getOverrideFileCore1() const = 0;
	virtual const std::string& getOverrideFileCore2() const = 0;
	virtual const std::string& getOverrideFileTitle() const = 0;
	virtual const std::string& getSavingText() const = 0;
	virtual const std::string& getPleaseWaitText() const = 0;

	/*SPLASHSCREEN_LANGUAGE_HEADERS*/

	virtual const std::string& getSceneOuputFileSelectText() const = 0;
	virtual const std::string& getDefaultModelText() const = 0;
	virtual const std::string& getSetModelAsDefaultCore() const = 0;
	virtual const std::string& getSetModelAsDefaultTitle() const = 0;
	virtual const std::string& getExitButtonText() const = 0;
	virtual const std::string& getLoadingText() const = 0;
	virtual const std::string& getModelOuputFileSelectText() const = 0;
	virtual const std::string& getXCurveText() const = 0;
	virtual const std::string& getYCurveText() const = 0;
	virtual const std::string& getZCurveText() const = 0;
	virtual const std::string& getHelpText() const = 0;

protected:
	Language();
};

}
/* namespace language */
} /* namespace utils */

#endif /* SRC_LANGUAGE_LANGUAGE_H_ */

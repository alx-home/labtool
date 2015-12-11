/*
 * Language.h
 *
 *  Created on: 5 janv. 2016
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_LANGUAGE_LANGUAGEPROXY_H_
#define SRC_LANGUAGE_LANGUAGEPROXY_H_

#include "Language.h"
#include "LanguageLoader.h"

namespace utils {
namespace language {

template<LanguageLoader::Language>
class LanguageProxy: public Language {
public:
	virtual const std::string& getFirstLabelisationText() const override;
	virtual const std::string& getLabelisationText() const override;
	virtual const std::string& getValidationFirstLabelisationText() const override;
	virtual const std::string& getValidationLabelisationText() const override;
	virtual const std::string& getAutoModeText() const override;
	virtual const std::string& getEditText() const override;
	virtual const std::string& getAutoModeEndedText() const override;
	virtual const std::string& getAutoModeWaitText() const override;
	virtual const std::string& getEmptyCurvesButtonText() const override;

	/*C3DREADER_LANGUAGE_HEADERS*/

	virtual const std::string& getNumberOfMarker() const override;
	virtual const std::string& getNumberOfFrame() const override;
	virtual const std::string& getFirstFrameNbr() const override;
	virtual const std::string& getLastFrameNbr() const override;
	virtual const std::string& getScaleFactor() const override;
	virtual const std::string& getInvalidDataFormat() const override;
	virtual const std::string& getAnalogueDatasNotImplemented() const override;
	virtual const std::string& getAquisitionFrequency() const override;
	virtual const std::string& getProcessorUsed() const override;
	virtual const std::string& getInvalidProcessorType() const override;
	virtual const std::string& getParameterLabelsNotFound() const override;
	virtual const std::string& getEntityGroupNotFound1() const override;
	virtual const std::string& getEntityGroupNotFound2() const override;
	virtual const std::string& getInvalidTypeOrNumberOf3DPoints() const override;
	virtual const std::string& getFrameReading1() const override;
	virtual const std::string& getFrameReading2() const override;
	virtual const std::string& getC3dIntegerDatasNotImplemented() const override;
	virtual const std::string& getInvalidParameterType1() const override;
	virtual const std::string& getInvalidParameterType2() const override;
	virtual const std::string& getCharacterType() const override;
	virtual const std::string& getIntegerType() const override;
	virtual const std::string& getFloatType() const override;
	virtual const std::string& getByteType() const override;
	virtual const std::string& getModelPrefixSizeError1() const override;
	virtual const std::string& getModelPrefixSizeError2() const override;
	virtual const std::string& getScenePrefixSizeError1() const override;
	virtual const std::string& getScenePrefixSizeError2() const override;
	virtual const std::string& getParameterChildOverflowException1() const override;
	virtual const std::string& getParameterChildOverflowException2() const override;
	virtual const std::string& getParameterChildOverflowException3() const override;
	virtual const std::string& getParameterChildOverflowException4() const override;

	/*CONTROLLER_LANGUAGE_HEADERS*/

	virtual const std::string& getFrameNbr() const override;
	virtual const std::string& getNbPoints() const override;

	/*MEX_LANGUAGE_HEADERS*/

	virtual const std::string& getUsage1() const override;
	virtual const std::string& getUsage2() const override;

	/*EDITOR_LANGUAGE_HEADERS*/

	virtual const std::string& getSplitFrames() const override;
	virtual const std::string& getSplitNextFrames() const override;
	virtual const std::string& getSplitPreviousFrames() const override;
	virtual const std::string& getSplitAllFrames() const override;
	virtual const std::string& getLinkSupression() const override;
	virtual const std::string& getMarkerRename() const override;
	virtual const std::string& getLinkMarkers() const override;
	virtual const std::string& getAddMarkersToGroups() const override;
	virtual const std::string& getRemoveMarkersFromGroups() const override;
	virtual const std::string& getRemoveMarkerGroups() const override;
	virtual const std::string& getCreateGroupFromMarkers() const override;
	virtual const std::string& getSetGroupMargin() const override;

	/*LABELISER_MENU_LANGUAGE_HEADERS*/

	virtual const std::string& getAutoButtonText() const override;
	virtual const std::string& getValidateButtonText() const override;
	virtual const std::string& getCancelButtonText() const override;
	virtual const std::string& getStopButtonText() const override;
	virtual const std::string& getFirstLabelisationButtonText() const override;
	virtual const std::string& getLabeliseButtonText() const override;

	/*MESSAGES_BOX_LANGUAGE_HEADERS*/

	virtual const std::string& getLabelisationNotEndedCore() const override;
	virtual const std::string& getLabelisationNotEndedTitle() const override;
	virtual const std::string& getSaveBeforeExitCore() const override;
	virtual const std::string& getSaveBeforeExitTitle() const override;
	virtual const std::string& getSaverErrorCore1() const override;
	virtual const std::string& getSaverErrorCore2() const override;
	virtual const std::string& getSaverErrorTitle() const override;

	/*PLOT_MOUSE_MENU_LANGUAGE_HEADERS*/

	virtual const std::string& getShowModelPointText() const override;
	virtual const std::string& getShowPredictionSpheresText() const override;
	virtual const std::string& getHidePredictionSpheresText() const override;
	virtual const std::string& getHideModelPointsText() const override;
	virtual const std::string& getShowLegendText() const override;
	virtual const std::string& getShowLabelsText() const override;
	virtual const std::string& getHideLabelsText() const override;
	virtual const std::string& getHideLegendText() const override;
	virtual const std::string& getShowLabelisationBoxesText() const override;
	virtual const std::string& getHideLabelisationBoxesText() const override;
	virtual const std::string& getAddSuppressionBoxesText() const override;
	virtual const std::string& getAddLabelisationBoxesText() const override;
	virtual const std::string& getShowGroupsText() const override;
	virtual const std::string& getHideGroupsText() const override;
	virtual const std::string& getRotateDatasText() const override;

	/*SPLASHSCREEN_SAVER_LANGUAGE_HEADERS*/

	virtual const std::string& getOuputFileSelectText() const override;
	virtual const std::string& getSaveSettingsFile() const override;
	virtual const std::string& getOverrideFileCore1() const override;
	virtual const std::string& getOverrideFileCore2() const override;
	virtual const std::string& getOverrideFileTitle() const override;
	virtual const std::string& getSavingText() const override;
	virtual const std::string& getPleaseWaitText() const override;

	/*SPLASHSCREEN_LANGUAGE_HEADERS*/

	virtual const std::string& getSceneOuputFileSelectText() const override;
	virtual const std::string& getDefaultModelText() const override;
	virtual const std::string& getSetModelAsDefaultCore() const override;
	virtual const std::string& getSetModelAsDefaultTitle() const override;
	virtual const std::string& getExitButtonText() const override;
	virtual const std::string& getLoadingText() const override;
	virtual const std::string& getModelOuputFileSelectText() const override;
	virtual const std::string& getXCurveText() const override;
	virtual const std::string& getYCurveText() const override;
	virtual const std::string& getZCurveText() const override;
	virtual const std::string& getHelpText() const override;

	LanguageProxy();
	virtual ~LanguageProxy();
};

template class LanguageProxy<LanguageLoader::FR> ;

}/* namespace language */
} /* namespace utils */

#endif /* SRC_LANGUAGE_LANGUAGEPROXY_H_ */

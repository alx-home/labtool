/*
 * Plot.cxx
 *
 *  Created on: 27 oct. 2015
 *      Author: Alexandre GARCIN
 */

#include "Plot3.h"

#ifdef SRC_PLOT_PLOT3_H_
#ifndef SRC_PLOT_PLOT3_CXX_
#define SRC_PLOT_PLOT3_CXX_

#include <tmwtypes.h>
#include <matrix.h>
#include <mex.h>
#include <functional>
#include <iostream>

Plot3::Plot3(Plot3 const& plot) :
		X(plot.X), Y(plot.Y), Z(plot.Z), arg(plot.arg), hold(plot.hold), figure(plot.figure) {
}

Plot3::Plot3(const vnl_matrix<double>& x, const vnl_matrix<double>& y, const vnl_matrix<double>& z, const std::string& arg,
		unsigned short figure, bool hold) :
		X(x), Y(y), Z(z), arg(arg), hold(hold), figure(figure) {
}

Plot3::~Plot3() {

}

Plot3& Plot3::setAxisEqual() {
	axisEqual = true;
	return *this;
}

void Plot3::setPreProperties() {

	if (!hold && shouldBeReseted) {
		mxArray *array2[1];
		array2[0] = mxCreateDoubleScalar(figure);
		mexCallMATLAB(0, nullptr, 1, array2, "close");
		mxDestroyArray(array2[0]);
	}

	mxArray *array2[1];
	if (hold)
		array2[0] = mxCreateString("on");
	else
		array2[0] = mxCreateString("off");
	mexCallMATLAB(0, nullptr, 1, array2, "hold");
	mxDestroyArray(array2[0]);
}

Plot3& Plot3::setSizeAndPos(double x, double y, double width, double height) {
	this->width = width;
	this->height = height;
	this->xPos = x;
	this->yPos = y;

	return *this;
}

void Plot3::setPostProperties(double handle) {
	if (axisEqual) {
		mxArray *array[1];
		array[0] = mxCreateString("equal");
		mexCallMATLAB(0, nullptr, 1, array, "axis");
		mxDestroyArray(array[0]);
	}

	if (!dispAxis) {
		mxArray *array[1];
		array[0] = mxCreateString("off");

		mexCallMATLAB(0, nullptr, 1, array, "axis");
		mxDestroyArray(array[0]);
	}

	if (color.size() > 0) {
		mxArray *array;
		array = mxCreateString(color.c_str());
		mexSet(figure, "color", array);

		mxDestroyArray(array);
	}

	if (labels.size() > 0) {
		mxArray *array;
		const mwSize size = (mwSize) labels.size();

		array = mxCreateCellArray(1, &size);

		for (unsigned int i = 0; i < labels.size(); ++i) {
			mxArray* cell = mxCreateString(labels[i].c_str());
			mxSetCell(array, i, cell);
		}

		mxArray* array2[2] = { mxCreateDoubleScalar(handle), array };

		mexCallMATLAB(0, nullptr, 2, array2, "customDataCursor");

		mxDestroyArray(array2[0]);
		mxDestroyArray(array2[1]);
	}

	if (this->title.size()) {
		mxArray *array[1];

		array[0] = mxCreateString(title.c_str());
		mexCallMATLAB(0, nullptr, 1, array, "title");
		mxDestroyArray(array[0]);
	}

	if (this->figureTitle.size()) {
		mxArray *array;
		array = mxCreateString(figureTitle.c_str());
		mexSet(figure, "name", array);
		mxDestroyArray(array);

		array = mxCreateString("off");
		mexSet(figure, "numbertitle", array);
		mxDestroyArray(array);
	}

	if (this->legende.size()) {
		unsigned int nb = this->legende.size() + (this->legendeLocation.size() ? 2 : 0);
		mxArray *array[nb];

		for (unsigned int i = 0; i < this->legende.size(); ++i)
			array[i] = mxCreateString(this->legende[i].c_str());

		if (legendeLocation.size()) {
			array[this->legende.size()] = mxCreateString("Location");
			array[this->legende.size() + 1] = mxCreateString(this->legendeLocation.c_str());
		}

		mexCallMATLAB(0, nullptr, nb, array, "legend");

		for (unsigned int i = 0; i < nb; ++i)
			mxDestroyArray(array[i]);
	}

	if (this->xPos >= 0) {
		mxArray *array[2] = { mxCreateString("normalized"), mxCreateDoubleMatrix(1, 4, mxREAL) };

		double* ptr = mxGetPr(array[1]);

		ptr[0] = this->xPos;
		ptr[1] = this->yPos;
		ptr[2] = this->xPos + this->width;
		ptr[3] = this->yPos + this->height;

		mexSet(figure, "units", array[0]);
		mexSet(figure, "outerposition", array[1]);

		mxDestroyArray(array[0]);
		mxDestroyArray(array[1]);
	}
}

Plot3& Plot3::displayAxis(bool flag) {
	dispAxis = flag;

	return *this;
}

Plot3& Plot3::setBackgroundColor(const std::string& color) {
	this->color = color;

	return *this;
}

Plot3& Plot3::setLabels(const std::vector<std::string>& labels) {
	this->labels = labels;

	return *this;
}

Plot3& Plot3::setLegende(const std::vector<std::string>& legende, std::string location) {
	this->legende = legende;
	this->legendeLocation = location;

	return *this;
}

Plot3& Plot3::hittable(bool flag) {
	this->isHittable = flag;

	return *this;
}

Plot3& Plot3::reopen(bool flag) {
	this->shouldBeReseted = flag;

	return *this;
}

Plot3& Plot3::setMarkerSize(double size) {
	this->markerSize = size;

	return *this;
}

Plot3& Plot3::setTitle(const std::string& title) {
	this->title = title;

	return *this;
}

Plot3& Plot3::setFigureTitle(const std::string& title) {
	this->figureTitle = title;

	return *this;
}

void Plot3::plot() {
	unsigned short nb = markerSize > 0 ? 8 : 6;

	mxArray* array[nb];
	array[0] = mxCreateDoubleMatrix(X.rows(), X.cols(), mxREAL);
	array[1] = mxCreateDoubleMatrix(Y.rows(), Y.cols(), mxREAL);
	array[2] = mxCreateDoubleMatrix(Z.rows(), Z.cols(), mxREAL);
	array[3] = mxCreateString(arg.c_str());
	array[4] = mxCreateString("HitTest");
	array[5] = mxCreateString(isHittable ? "on" : "off");

	if (markerSize > 0) {
		array[6] = mxCreateString("MarkerSize");
		array[7] = mxCreateDoubleScalar(markerSize);
	}

	{
		const vnl_matrix<double>& matrix = X;
		double* ptr = mxGetPr(array[0]);

		for (unsigned int i = 0; i < matrix.rows(); ++i)
			for (unsigned int j = 0; j < matrix.cols(); ++j)
				ptr[i + j * matrix.rows()] = matrix(i, j);
	}

	{
		const vnl_matrix<double>& matrix = Y;
		double* ptr = mxGetPr(array[1]);

		for (unsigned int i = 0; i < matrix.rows(); ++i)
			for (unsigned int j = 0; j < matrix.cols(); ++j)
				ptr[i + j * matrix.rows()] = matrix(i, j);
	}

	{
		const vnl_matrix<double>& matrix = Z;
		double* ptr = mxGetPr(array[2]);

		for (unsigned int i = 0; i < matrix.rows(); ++i)
			for (unsigned int j = 0; j < matrix.cols(); ++j)
				ptr[i + j * matrix.rows()] = matrix(i, j);
	}

	{
		mxArray* array2[1] = { mxCreateDoubleScalar(figure) };
		mexCallMATLAB(0, nullptr, 1, array2, "figure");
		mxDestroyArray(array2[0]);
	}

	setPreProperties();

	mxArray* outputs[1];

	mexCallMATLAB(1, outputs, nb, array, "plot3");

	double handle = mxGetScalar(outputs[0]);

	mxDestroyArray(outputs[0]);

	setPostProperties(handle);

	mexCallMATLAB(0, nullptr, 0, nullptr, "drawnow");

	for (unsigned short i = 0; i < nb; ++i)
		mxDestroyArray(array[i]);
}

#endif
#endif

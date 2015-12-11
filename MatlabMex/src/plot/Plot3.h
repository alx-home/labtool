/*
 * Plot.h
 *
 *  Created on: 27 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_PLOT_PLOT3_H_
#define SRC_PLOT_PLOT3_H_

#include <vxl/core/vnl/vnl_matrix.h>
#include <string>
#include <vector>

class Plot3 {
public:
	Plot3(const vnl_matrix<double>& x, const vnl_matrix<double>& y, const vnl_matrix<double>& z, const std::string& arg,
			unsigned short figure = 1, bool hold = true);
	Plot3(Plot3 const&);
	virtual ~Plot3();

	void plot();
	Plot3& setAxisEqual();
	Plot3& displayAxis(bool flag);
	Plot3& setBackgroundColor(const std::string& color);
	Plot3& setLabels(const std::vector<std::string>& labels);
	Plot3& hittable(bool flag);
	Plot3& reopen(bool flag);
	Plot3& setMarkerSize(double size);
	Plot3& setTitle(const std::string& title);
	Plot3& setFigureTitle(const std::string& title);
	Plot3& setLegende(const std::vector<std::string>& legende, std::string location = "");
	Plot3& setSizeAndPos(double x, double y, double width, double height);
	/*Plot3& dataCallBackOnClick(
	 std::function<void(vnl_vector<double>)> function);
	 */
private:
	const vnl_matrix<double>& X;
	const vnl_matrix<double>& Y;
	const vnl_matrix<double>& Z;
	std::string arg;
	bool hold;
	unsigned short figure;
	bool axisEqual = false;
	bool dispAxis = true;
	std::string color;
	std::vector<std::string> labels;
	bool isHittable = true;
	bool shouldBeReseted = false;
	double markerSize = -1.0;
	std::string title;
	std::string figureTitle;
	std::vector<std::string> legende;
	std::string legendeLocation;
	double xPos = -1.0;
	double yPos = -1.0;
	double width = -1.0;
	double height = -1.0;

	void setPreProperties();
	void setPostProperties(double handle);
};

#endif /* SRC_PLOT_PLOT3_H_ */

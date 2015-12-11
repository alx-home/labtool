/*
 * DataStruct.cxx
 *
 *  Created on: 27 oct. 2015
 *      Author: Alexandre GARCIN
 */

#include "DataStruct.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <iostream>
#include <iterator>

#include "../window/Layer/content/Buttons/Button.h"
#include "../window/Layer/content/plot/line/Line.h"
#include "../window/Layer/content/plot/point/Selector.h"
#include "../window/Layer/content/plot/Plot3d.h"
#include "../window/Layer/content/TextLayer.h"
#include "../window/Layer/disposition/ConstrainedLayer.h"
#include "../window/Layer/disposition/SplitLayer.h"
#include "../window/Layer/disposition/StakeLayer.h"
#include "../window/Layer/EmptyLayer.h"
#include "../window/Layer/Layer.h"
#include "../window/Window.h"

#ifdef SRC_DATASTRUCT_H_
#ifndef SRC_DATASTRUCT_CXX_
#define SRC_DATASTRUCT_CXX_

namespace generic {

DataStruct::Struct() :
		datas(vnl_matrix<double>()) {
}

#ifdef MATLAB
DataStruct::Struct(vnl_matrix<double>& xDatas, vnl_matrix<double>& yDatas, vnl_matrix<double>& zDatas)
{
	datas.set_size(xDatas.size(), 3);

	for (unsigned int i = 0; i < xDatas.size(); ++i) {
		datas(i, 0) = xDatas(i, 0);
		datas(i, 1) = yDatas(i, 0);
		datas(i, 2) = zDatas(i, 0);
	}
}
#endif

DataStruct::~Struct() {
}

#ifdef MATLAB
void DataStruct::write(vnl_matrix<double>& xDatas, vnl_matrix<double>& yDatas, vnl_matrix<double>& zDatas) {
	/*

	 xDatas.set_size(datas.rows(), 1);
	 yDatas.set_size(datas.rows(), 1);
	 zDatas.set_size(datas.rows(), 1);*/

	xDatas = this->datas.get_n_columns(0, 1);
	yDatas = this->datas.get_n_columns(1, 1);
	zDatas = this->datas.get_n_columns(2, 1);
}
#endif
}
 // namespace generic

#endif
#endif

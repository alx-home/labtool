/*
 * DataStruct.h
 *
 *  Created on: 26 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_DATASTRUCT_H_
#define SRC_DATASTRUCT_H_

#ifdef MATLAB
#include <templateSpec/UnorderedMap.hpp>
#include <templateSpec/Struct.hpp>
#include <templateSpec/String.hpp>
#include <templateSpec/VnlMatrix.hpp>
#include <templateSpec/numeric/Double.hpp>
#endif
#include <vxl/core/vnl/vnl_matrix.h>
#include <memory>
#include <vector>

namespace point {
class Selector;
} /* namespace point */
namespace window {
class Plot3d;
} /* namespace window */

#ifdef MATLAB
#define xData__ generic::String<'x', 'd', 'a', 't', 'a'>
#define yData__ generic::String<'y', 'd', 'a', 't', 'a'>
#define zData__ generic::String<'z', 'd', 'a', 't', 'a'>

namespace generic {

template<>
class Struct<StructDefinition<vnl_matrix<double>, vnl_matrix<double>, vnl_matrix<double>>,
xData__, yData__, zData__> {
public:
	Struct();
	Struct(vnl_matrix<double>& xDatas, vnl_matrix<double>& yDatas, vnl_matrix<double>& zDatas);
	virtual ~Struct();

	void write(vnl_matrix<double>& xDatas, vnl_matrix<double>& yDatas, vnl_matrix<double>& zDatas);

	vnl_matrix<double> datas = vnl_matrix<double>();
	std::vector<double> probabilties = std::vector<double>();
};

typedef class Struct<StructDefinition<vnl_matrix<double>, vnl_matrix<double>, vnl_matrix<double>>, xData__,yData__,zData__>DataStruct;

}
// namespace generic

#else

namespace generic {
/**
 * @brief Structure contenant les données à labelliser et/ou du modèles
 *
 * @class Struct
 * @author Alexandre GARCIN
 * @date 26 oct. 2015
 */
class Struct {
public:
	Struct();
	virtual ~Struct();

	/**
	 * les données à labelliser et ou servant de modèle
	 */
	vnl_matrix<double> datas;
};

typedef Struct DataStruct;

}
// namespace generic

#endif

#endif /* SRC_DATASTRUCT_H_ */

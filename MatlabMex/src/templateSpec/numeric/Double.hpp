/*
 * Bool.hpp
 *
 *  Created on: 13 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_TEMPLATESPEC_BOOL_HPP_
#define SRC_TEMPLATESPEC_BOOL_HPP_

#include <matrix.h>
#include <exception>
#include <iostream>

#include "../../MatlabMex.h"

namespace generic {

template<typename ... Outputs, typename ... Inputs>
class Streamer<Output<Outputs...>, Input<Inputs...>, double> {
public:
	inline static double getInput(unsigned short index, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
		if (!mxIsDouble(prhs[index])) {
			std::cerr << "Le paramètre n°" << (index + 1) << " est incorrecte\n\texpected real, received another type" << std::endl;
			throw new std::exception();
		}

		double* value = mxGetPr(mxDuplicateArray(prhs[index]));
		return value[0];
	}

	inline static void setOutput(unsigned short index, double& value, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

		double* output = mxGetPr(plhs[index] = mxCreateDoubleMatrix(1, 1, mxREAL));

		output[0] = (double) value;
	}
};

} /* namespace generic */

#endif /* SRC_TEMPLATESPEC_BOOL_HPP_ */

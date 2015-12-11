/*
 * Bool.hpp
 *
 *  Created on: 13 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_TEMPLATESPEC_BOOL_HPP_
#define SRC_TEMPLATESPEC_BOOL_HPP_

#include <matrix.h>
#include <climits>
#include <exception>
#include <iostream>

#include "../../MatlabMex.h"

namespace generic {

template<typename ... Outputs, typename ... Inputs>
class Streamer<Output<Outputs...>, Input<Inputs...>, int> {
public:
	inline static int getInput(unsigned short index, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
		if (!mxIsDouble(prhs[index])) {
			std::cerr << "Le paramètre n°" << (index + 1) << " est incorrecte\n\texpected real, received another type" << std::endl;
			throw new std::exception();
		}

		double* value = mxGetPr(mxDuplicateArray(prhs[index]));

		if (value[0] > INT_MAX || value[0] < INT_MIN) {
			std::cerr << "Error : integer overflow du parametre n°" << (index + 1) << std::endl;
			throw new std::exception();
		}

		return value[0];
	}

	inline static void setOutput(unsigned short index, int& integer, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

		double* output = mxGetPr(plhs[index] = mxCreateDoubleMatrix(1, 1, mxREAL));

		output[0] = (double) integer;
	}
};

} /* namespace generic */

#endif /* SRC_TEMPLATESPEC_BOOL_HPP_ */

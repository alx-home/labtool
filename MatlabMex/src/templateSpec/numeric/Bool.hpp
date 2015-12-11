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
class Streamer<Output<Outputs...>, Input<Inputs...>, bool> {
public:
	inline static bool getInput(unsigned short index, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
		if (!mxIsDouble(prhs[index])) {
			std::cerr << "Le paramètre n°" << (index + 1) << " est incorrecte\n\texpected boolean, received another type" << std::endl;
			throw new std::exception();
		}

		double* matlabMatrix = mxGetPr(mxDuplicateArray(prhs[index]));
		return matlabMatrix[0] != 0;
	}

	inline static void setOutput(unsigned short index, bool& boolean, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

		double* output = mxGetPr(plhs[index] = mxCreateDoubleMatrix(1, 1, mxREAL));

		output[0] = (double) boolean;
	}
};

} /* namespace generic */

#endif /* SRC_TEMPLATESPEC_BOOL_HPP_ */

/*
 * VnlMatrix.hpp
 *
 *  Created on: 12 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_TEMPLATESPEC_VNLMATRIX_HPP_
#define SRC_TEMPLATESPEC_VNLMATRIX_HPP_

#include <matrix.h>
#include <tmwtypes.h>
#include <vxl/core/vnl/vnl_matrix.h>
#include <exception>
#include <iostream>

#include "../MatlabMex.h"

namespace generic {

template<typename ... Outputs, typename ... Inputs>
class Streamer<Output<Outputs...>, Input<Inputs...>, vnl_matrix<double>> {
public:
	inline static vnl_matrix<double> getInput(unsigned short index, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

		const mwSize* dim = mxGetDimensions(prhs[index]);
		int numDims = mxGetNumberOfDimensions(prhs[index]);

		if (numDims != 2) {
			std::cerr << "La dimension du paramètre n°" << (index + 1) << " est incorrecte\n" << "\texpected 2, received " << numDims
					<< std::endl;
			throw new std::exception();
		}

		vnl_matrix<double> matrix(dim[0], dim[1]);

		double* matlabMatrix = mxGetPr(mxDuplicateArray(prhs[index]));

		for (int i = 0; i < dim[0]; ++i)
			for (int j = 0; j < dim[1]; ++j)
				matrix(i, j) = matlabMatrix[i + j * dim[0]];

		return matrix;
	}

	inline static void setOutput(unsigned short index, vnl_matrix<double>& matrix, int nlhs, mxArray *plhs[], int nrhs,
			const mxArray *prhs[]) {

		double* output = mxGetPr(plhs[index] = mxCreateDoubleMatrix(matrix.rows(), matrix.cols(), mxREAL));

		for (int i = 0; i < matrix.rows(); ++i)
			for (int j = 0; j < matrix.cols(); ++j)
				output[i + j * matrix.rows()] = matrix(i, j);
	}
};

} /* namespace generic */

#endif /* SRC_TEMPLATESPEC_VNLMATRIX_HPP_ */

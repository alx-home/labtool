/*
 * Struct.hpp
 *
 *  Created on: 13 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_TEMPLATESPEC_CELLS_HPP_
#define SRC_TEMPLATESPEC_CELLS_HPP_

#include <matrix.h>
#include <stddef.h>
#include <tmwtypes.h>
#include <exception>
#include <iostream>
#include <vector>

#include "../MatlabMex.h"

namespace generic {

template<typename ... Outputs, typename ... Inputs, typename Type>
class Streamer<Output<Outputs...>, Input<Inputs...>, std::vector<Type>> {
public:
	inline static std::vector<Type> getInput(unsigned short index, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
		const mxArray* cells = prhs[index];
		std::vector<Type> result;

		if (!mxIsCell(cells)) {
			std::cerr << "Le paramètre n°" << (index + 1) << " est incorrecte\n\tle parametre n'est pas de type Cells" << std::endl;
			throw new std::exception();
		}

		unsigned int taille = mxGetN(cells);
		{
			unsigned int tmp = mxGetM(cells);
			taille = taille > tmp ? taille : tmp;
		}

		for (unsigned int i = 0; i < taille; ++i) {
			const mxArray* cell;

			if ((cell = mxGetCell(cells, i)) == NULL) {
				std::cerr << "Le paramètre n°" << (index + 1) << " est incorrecte\n\tla cellule n°" << i << " du paramètre n°" << index
						<< "est incorrecte\n" << std::endl;
				throw new std::exception();
			} else {
				result.push_back(Streamer<Output<Outputs...>, Input<Inputs...>, Type>::getInput(index, nlhs, plhs, nrhs, &cell - index));
			}
		}

		return result;
	}

	inline static void setOutput(unsigned short index, std::vector<Type>& cells, int nlhs, mxArray *plhs[], int nrhs,
			const mxArray *prhs[]) {
		mwSize taille = cells.size();

		plhs[index] = mxCreateCellArray(1, &taille);

		for (unsigned int i = 0; i < cells.size(); ++i) {
			mxArray* cell;

			Streamer<Output<Outputs...>, Input<Inputs...>, Type>::setOutput(index, cells[i], nlhs, &cell - index, nrhs, prhs);

			mxSetCell(plhs[index], i, cell);
		}
	}
};
}
/* namespace generic */

#endif /* SRC_TEMPLATESPEC_CELLS_HPP_ */

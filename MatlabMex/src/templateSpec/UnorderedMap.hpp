/*
 * Map
 *
 *  Created on: 13 nov. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_TEMPLATESPEC_MAP_HPP_
#define SRC_TEMPLATESPEC_MAP_HPP_

#include <matrix.h>
#include <stddef.h>
#include <tmwtypes.h>
#include <exception>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "../MatlabMex.h"

namespace generic {

template<typename ... Outputs, typename ... Inputs, typename Type>
class Streamer<Output<Outputs...>, Input<Inputs...>, std::unordered_map<std::string, Type>> {
public:
	inline static std::unordered_map<std::string, Type> getInput(unsigned short index, int nlhs, mxArray *plhs[], int nrhs,
			const mxArray *prhs[]) {
		const mxArray* unordered_map = prhs[index];
		std::unordered_map<std::string, Type> result;

		if (!mxIsStruct(unordered_map)) {
			std::cerr << "Le paramètre n°" << (index + 1) << " est incorrecte\n\tle parametre n'est pas de type Struct" << std::endl;
			throw new std::exception();
		}

		unsigned int taille = mxGetNumberOfFields(unordered_map);

		for (unsigned int i = 0; i < taille; ++i) {
			const mxArray* field;

			std::string fieldName = mxGetFieldNameByNumber(unordered_map, i);

			if ((field = mxGetField(unordered_map, 0, fieldName.c_str())) == NULL) {
				std::cerr << "Le paramètre n°" << (index + 1) << " est incorrecte\n\tle champ n°" << i << " du paramètre n°" << index
						<< "est incorrecte\n" << std::endl;
				throw new std::exception();
			}

			result[fieldName] = Streamer<Output<Outputs...>, Input<Inputs...>, Type>::getInput(index, nlhs, plhs, nrhs, &field - index);
		}

		return result;
	}

	inline static void setOutput(unsigned short index, std::unordered_map<std::string, Type>& unordered_map, int nlhs, mxArray *plhs[],
			int nrhs, const mxArray *prhs[]) {
		/*mwSize taille = unordered_map.size();

		 plhs[index] = mxCreateCellArray(1, &taille);

		 for (unsigned int i = 0; i < cells.size(); ++i) {
		 mxArray* cell;

		 Streamer<Output<Outputs...>, Input<Inputs...>, Type>::setOutput(index, unordered_map[i], nlhs, &cell - index, nrhs, prhs);

		 mxSetCell(plhs[index], i, cell);
		 }todo*/
	}
};
}
/* namespace generic */

#endif /* SRC_TEMPLATESPEC_MAP_HPP_ */

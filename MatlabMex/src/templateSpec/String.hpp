/*
 * String.hpp
 *
 *  Created on: 26 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_TEMPLATESPEC_STRING_HPP_
#define SRC_TEMPLATESPEC_STRING_HPP_

#include <matrix.h>
#include <exception>
#include <iostream>
#include <string>

#include "../MatlabMex.h"

namespace generic {

template<typename ... Outputs, typename ... Inputs>
class Streamer<Output<Outputs...>, Input<Inputs...>, std::string> {
public:
	inline static std::string getInput(unsigned short index, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
		const mxArray* string = prhs[index];

		if (!mxIsChar(string)) {
			std::cerr << "Le paramètre n°" << (index + 1) << " est incorrecte\n" << "\tle paramètre n'est pas une chaine de charactères"
					<< std::endl;
			throw new std::exception();
		}

		unsigned int buffLength = mxGetM(string);
		{
			unsigned int tmp = mxGetN(string);
			buffLength = buffLength > tmp ? buffLength : tmp;
		}

		++buffLength;

		char buff[buffLength];

		if (mxGetString(string, buff, buffLength)) {
			std::cerr << "Le paramètre n°" << (index + 1) << " est incorrecte\n" << "\tImpossible de lire la chaine de charactère"
					<< std::endl;
			throw new std::exception();
		}

		return std::string(buff);
	}

	inline static void setOutput(unsigned short index, std::string& string, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
		plhs[index] = mxCreateString(string.c_str());
	}
};

} /* namespace generic */

#endif /* SRC_TEMPLATESPEC_STRING_HPP_ */

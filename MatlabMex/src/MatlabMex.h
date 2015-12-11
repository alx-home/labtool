/*
 * MatlabMex.h
 *
 *  Created on: 9 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_MATLABMEX_H_
#define SRC_MATLABMEX_H_

#include <matrix.h>
#include <mex.h>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include "CoutMatlab.h"

template<typename ... Args>
struct Output {
};

template<typename ... Args>
struct Input {
};

namespace generic {
//todo declaration inside cpp
template<typename, typename, typename >
class Streamer;

template<typename ... Outputs, typename ... Inputs, typename T>
class Streamer<Output<Outputs...>, Input<Inputs...>, T> {
public:
	inline static T getInput(unsigned short index, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

	inline static void setOutput(unsigned short index, T output, int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);
};

template<typename, typename >
class Wrapper;

template<typename ... Outputs, typename ... Inputs>
class Wrapper<Output<Outputs...>, Input<Inputs...>> {
public:
	Wrapper() {

	}
	virtual ~Wrapper() {

	}

	inline static void wrap(std::function<void(Outputs&..., Inputs& ...)> func, int nlhs, mxArray *plhs[], int nrhs,
			const mxArray *prhs[]) {
		OutputWrapper_<0, Output<Outputs...>, Output<>>::wrap(func, nlhs, plhs, nrhs, prhs);
	}

protected:

	template<unsigned short, typename, typename >
	class OutputWrapper_;

	template<unsigned short index, typename T, typename ...LeftTypes, typename ... SettedTypes>
	class OutputWrapper_<index, Output<T, LeftTypes...>, Output<SettedTypes...>> {
	public:
		inline static void wrap(std::function<void(Outputs&..., Inputs& ...)>& func, int nlhs, mxArray *plhs[], int nrhs,
				const mxArray *prhs[], SettedTypes& ... outputs) {
			T t;

			OutputWrapper_<index + 1, Output<LeftTypes...>, Output<SettedTypes..., T>>::wrap(func, nlhs, plhs, nrhs, prhs, outputs..., t);

			Streamer<Output<Outputs...>, Input<Inputs...>, T>::setOutput(index, t, nlhs, plhs, nrhs, prhs);
		}
	};

	template<unsigned short index, typename ... SettedTypes>
	class OutputWrapper_<index, Output<>, Output<SettedTypes...>> {
	public:
		inline static void wrap(std::function<void(Outputs&..., Inputs& ...)>& func, int nlhs, mxArray *plhs[], int nrhs,
				const mxArray *prhs[], SettedTypes&... outputs) {

			InputWrapper_<0, Input<Inputs...>, Input<>>::wrap(func, nlhs, plhs, nrhs, prhs, outputs...);
		}
	};

	template<unsigned short, typename, typename >
	class InputWrapper_;

	template<unsigned short index, typename T, typename ... LeftTypes, typename ... SettedTypes>
	class InputWrapper_<index, Input<T, LeftTypes...>, Input<SettedTypes...>> {
	public:
		inline static void wrap(std::function<void(Outputs&..., Inputs& ...)>& func, int nlhs, mxArray *plhs[], int nrhs,
				const mxArray *prhs[], Outputs&... outputs, SettedTypes& ... inputs) {
			T value = Streamer<Output<Outputs...>, Input<Inputs...>, T>::getInput(index, nlhs, plhs, nrhs, prhs);

			InputWrapper_<index + 1, Input<LeftTypes...>, Input<SettedTypes..., T>>::wrap(func, nlhs, plhs, nrhs, prhs, outputs...,
					inputs..., value);
		}
	};

	template<unsigned short index, typename ... SettedTypes>
	class InputWrapper_<index, Input<>, Input<SettedTypes...>> {
	public:
		inline static void wrap(std::function<void(Outputs&..., Inputs& ...)>& func, int nlhs, mxArray *plhs[], int nrhs,
				const mxArray *prhs[], Outputs&... outputs, Inputs&...inputs) {
			func(outputs..., inputs...);
		}
	};
};

}
// namespace generic

template<typename, typename >
class MatlabMex;

template<typename ... Outputs, typename ... Inputs>
class MatlabMex<Output<Outputs...>, Input<Inputs...>> {
public:

	inline static void usage();
	inline static void run(Outputs&... outputs, Inputs&... inputs);

	inline static void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
		try {
			if (nrhs != sizeof...(Inputs)) {
				std::cerr << "Le nombre d'arguments passés à la fonction \"" << name << "\" est incorrect\n";
				std::cerr << "\texpected " << sizeof...(Inputs) << ", received " << nrhs << std::endl;

				throw std::exception();
			}

			if (nlhs != 0 && nlhs != sizeof...(Outputs)) {
				std::cerr << "Le nombre d'arguments en sortie de la fonction \"" <<name<< "\" est incorrect\n";
				std::cerr << "\texpected " << sizeof...(Outputs) << ", received " << nlhs << std::endl;

				throw std::exception();
			}

			generic::Wrapper<Output<Outputs...>, Input<Inputs...>>::wrap(
			[](Outputs&... outputs, Inputs&... inputs) {
				run(outputs..., inputs...);
			},
			nlhs, plhs, nrhs, prhs);

			std::cout.flush();
			std::cerr.flush();

		} catch (...) {
			usage();
		}
	}

	virtual ~MatlabMex() {
	}

	MatlabMex() {
	}

	static std::string getName() {
		return name;
	}

protected:
	static std::string name;
};

#endif /* SRC_MATLABMEX_H_ */

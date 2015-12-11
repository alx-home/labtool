/*
 * Struct.hpp
 *
 *  Created on: 13 oct. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_TEMPLATESPEC_STRUCT_HPP_
#define SRC_TEMPLATESPEC_STRUCT_HPP_

#include <matrix.h>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "../MatlabMex.h"

namespace generic {

template<typename ...>
class Param;

template<char ... Chars_>
class String {
public:
	inline static const std::string& getString() {
		static const std::string str { { Chars_... } };
		return str;
	}
};

template<typename ... Strings_>
class Strings;

template<typename, typename, typename, typename, typename, typename, typename >
class StructBuilder;

template<typename ...>
class StructDefinition;

template<typename, typename, typename ...>
class Struct;
/*
 template<typename ... Types, typename ... FieldsName>
 class Struct<StructDefinition<Types...>, FieldsName...> {
 public:
 Struct(Types&... fields);

 virtual ~Struct() {}

 void write(Types&... fields);
 };*/

template<typename T, typename ... LeftTypes, typename ... SettedTypes, typename S, typename ... LeftNames, typename ... Types,
		typename ... FieldsName, typename ... Outputs, typename ... Inputs>
class StructBuilder<Param<T, LeftTypes...>, Param<SettedTypes...>, Strings<S, LeftNames...>, Param<Types...>, Strings<FieldsName...>,
		Output<Outputs...>, Input<Inputs...>> {
public:
	inline static Struct<StructDefinition<Types...>, FieldsName...> build(unsigned short index, int nlhs, mxArray *plhs[], int nrhs,
			const mxArray *prhs[], SettedTypes&... settedFieldValues) {

		const mxArray* field = mxGetField(prhs[index], 0, S::getString().c_str());
		if (field == NULL) {
			std::cerr << "Le paramètre n°" << (index + 1) << " est incorrecte\n"
					<< "\tLa structure passée en paramètre ne contient pas le champ \"" << S::getString() << "\"" << std::endl;
			throw new std::exception();
		}

		T fieldValue = Streamer<Output<Outputs...>, Input<Inputs...>, T>::getInput(index, nlhs, plhs, nrhs, &field - index);

		return StructBuilder<Param<LeftTypes...>, Param<SettedTypes..., T>, Strings<LeftNames...>, Param<Types...>, Strings<FieldsName...>,
				Output<Outputs...>, Input<Inputs...>>::build(index, nlhs, plhs, nrhs, prhs, settedFieldValues..., fieldValue);
	}
};

template<typename ... Types, typename ... FieldsName, typename ... Outputs, typename ... Inputs>
class StructBuilder<Param<>, Param<Types...>, Strings<>, Param<Types...>, Strings<FieldsName ...>, Output<Outputs...>, Input<Inputs...>> {
public:
	inline static Struct<StructDefinition<Types...>, FieldsName...> build(unsigned short index, int nlhs, mxArray *plhs[], int nrhs,
			const mxArray *prhs[], Types&... settedFieldValues) {
		return Struct<StructDefinition<Types...>, FieldsName...>(settedFieldValues...);
	}
};

template<typename, typename, typename, typename, typename, typename, typename >
class StructWritter;

template<typename T, typename ... LeftTypes, typename S, typename ... LeftNames, typename ... Types, typename ... FieldsName,
		typename ... Outputs, typename ... Inputs, typename ... SettedTypes>
class StructWritter<Param<T, LeftTypes...>, Param<SettedTypes...>, Strings<S, LeftNames...>, Param<Types...>, Strings<FieldsName...>,
		Output<Outputs...>, Input<Inputs...>> {
public:
	inline static void write(Struct<StructDefinition<Types...>, FieldsName...>& structure, unsigned short index, int nlhs, mxArray *plhs[],
			int nrhs, const mxArray *prhs[], unsigned int i, std::vector<const char*>& labels, SettedTypes&... settedTypeValues) {

		T field_;

		labels.push_back(S::getString().c_str());

		StructWritter<Param<LeftTypes...>, Param<SettedTypes..., T>, Strings<LeftNames...>, Param<Types...>, Strings<FieldsName...>,
				Output<Outputs...>, Input<Inputs...>>::write(structure, index, nlhs, plhs, nrhs, prhs, i + 1, labels, settedTypeValues...,
				field_);

		mxArray* field;

		Streamer<Output<Outputs...>, Input<Inputs...>, T>::setOutput(index, field_, nlhs, &field - index, nrhs, prhs);

		mxSetFieldByNumber(plhs[index], 0, i, field);
	}
};

template<typename ... Types, typename ... FieldsName, typename ... Outputs, typename ... Inputs>
class StructWritter<Param<>, Param<Types...>, Strings<>, Param<Types...>, Strings<FieldsName...>, Output<Outputs...>, Input<Inputs...>> {
public:
	inline static void write(Struct<StructDefinition<Types...>, FieldsName...>& structure, unsigned short index, int nlhs, mxArray *plhs[],
			int nrhs, const mxArray *prhs[], unsigned int i, std::vector<const char*>& labels, Types&... values) {
		const char** labels_ = &labels[0];
		plhs[index] = mxCreateStructMatrix(1, 1, i, labels_);

		structure.write(values...);
	}
};

template<typename ... Outputs, typename ... Inputs, typename ... Types, typename ... FieldsName>
class Streamer<Output<Outputs...>, Input<Inputs...>, Struct<StructDefinition<Types...>, FieldsName ...>> {
public:
	inline static Struct<StructDefinition<Types...>, FieldsName...> getInput(unsigned short index, int nlhs, mxArray *plhs[], int nrhs,
			const mxArray *prhs[]) {

		if (!mxIsStruct(prhs[index])) {
			std::cerr << "Le paramètre n°" << (index + 1) << " est incorrecte\n" << "\texpected struct, received another type" << std::endl;
			throw new std::exception();
		}

		return StructBuilder<Param<Types...>, Param<>, Strings<FieldsName...>, Param<Types...>, Strings<FieldsName...>, Output<Outputs...>,
				Input<Inputs...>>::build(index, nlhs, plhs, nrhs, prhs);
	}

	inline static void setOutput(unsigned short index, Struct<StructDefinition<Types...>, FieldsName...>& structure, int nlhs,
			mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
		std::vector<const char*> labels;

		StructWritter<Param<Types...>, Param<>, Strings<FieldsName...>, Param<Types...>, Strings<FieldsName...>, Output<Outputs...>,
				Input<Inputs...>>::write(structure, index, nlhs, plhs, nrhs, prhs, 0, labels);
	}
};

}
/* namespace generic */

#endif /* SRC_TEMPLATESPEC_STRUCT_HPP_ */

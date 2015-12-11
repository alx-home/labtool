/*
 * IdenticPropabilityException.h
 *
 *  Created on: 2 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_EXCEPTION_LABELLISATION_IDENTICPROPABILITYEXCEPTION_H_
#define SRC_EXCEPTION_LABELLISATION_IDENTICPROPABILITYEXCEPTION_H_

#include <exception>
#include <string>
#include <vector>

namespace exception {
namespace labelisation {

class IdenticPropabilityException: public std::exception {
public:
	IdenticPropabilityException(const std::vector<std::string>& labels);
	virtual ~IdenticPropabilityException();

	const std::vector<std::string>& getLabels() const;

private:
	std::vector<std::string> labels;
};

} /* namespace labellisation */
} /* namespace exception */

#endif /* SRC_EXCEPTION_LABELLISATION_IDENTICPROPABILITYEXCEPTION_H_ */

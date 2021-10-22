// File name: BaseOption.cpp
// Author: Li Jin Chen
// Exercise: 9.Group_A
// Description: Source file for the BaseOption class. It is the abstract class from which the EuropeanOption 
//		class and the PAmericanOption class are derived. It includes functionalities for setting and getting 
//		parameters. Calculations are delagated to derived classes. 


#include "BaseOption.hpp"
#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <iostream>
using namespace boost::math;

void BaseOption::init()
{
	// only risk-free rate is initialized in base class, as r is indepdendent of option characteristics
	param["r"] = 0.03;
	optType = "C";	// call as default type
}

void BaseOption::copy(const BaseOption& o2)
{
	param = o2.param;
	optType = o2.optType;
}

// Default constructor
BaseOption::BaseOption()
{
	init();
}

// Copy constructor
BaseOption::BaseOption(const BaseOption& o2)
{
	copy(o2);
}

// Constructor from parameters
BaseOption::BaseOption(const doubleMap& param0)
{
	param = param0;
	optType = "C";
}

// Constructor from option type
BaseOption::BaseOption(string optionType)
{
	init();
	optType = optionType;

	if (optType == "c")
		optType = "C";
}

// Constructor from parameters and option type
BaseOption::BaseOption(const doubleMap& param0, string optionType)
{
	param = param0;
	optType = optionType;

	if (optType == "c")
		optType = "C";
}

// Destructor
BaseOption::~BaseOption()
{

}

// selector functions
// get all double-type parameters
const doubleMap& BaseOption::getParam() const
{
	return param;
}

// get specific parameter
double BaseOption::getParam(string paramName) const
{
	return param.at(paramName);
}

// get option type
string BaseOption::getType() const
{
	return optType;
}

// modifier functions
// input all double-type parameters
void BaseOption::setParam(const doubleMap& param0)
{
	param = param0;
}

// set specific parameter
void BaseOption::setParam(string paramName, double newVal)
{
	param[paramName] = newVal;
}

// set option type
void BaseOption::setType(string newType)
{
	optType = newType;
}

// switch option type
void BaseOption::toggle()
{
	if (optType == "C")
		optType = "P";
	else
		optType = "C";
}

// overloaded = operator
BaseOption& BaseOption::operator = (const BaseOption& option2)
{
	if (this != &option2) copy(option2);
	return *this;
}

// overloaded [] operator for writing
double& BaseOption::operator [] (string paramName)
{
	return param[paramName];
}

// overloaded [] operator for reading
const double& BaseOption::operator [] (string paramName) const
{
	return param.at(paramName);
}
// File name: BaseMatrix.cpp
// Author: Li Jin Chen
// Exercise: 9.Group_B
// Description: Source file for the BaseMatrix class. It is the abstract class from which the EuropeanMatrix 
//		class and the PAmericanMatrix class are derived. It includes functionalities for setting and getting 
//		parameters. It also makes sure that all parameters are vectors of the same size. Calculations are 
//		delagated to derived classes. 


#include "BaseMatrix.hpp"
#include <cmath>
#include <sstream>
#include <algorithm>

// Mesh function is used for creating vector instances
// Mesh function with one input gives a one-member vector (can be double or string)
// Mesh function with three inputs gives a vector that spans a range

// Default constructor
BaseMatrix::BaseMatrix()
{
	// only risk-free rate is initialized in base class, as r is indepdendent of option characteristics
	param["r"] = Mesh(0.03);
	optType = Mesh<string>("C");	// call as default type
}

// Copy constructor
BaseMatrix::BaseMatrix(const BaseMatrix& source)
{
	param = source.param;
	optType = source.optType;
}

// Constructor from parameters
BaseMatrix::BaseMatrix(const vectorMap& param0)
{
	param = param0;
	optType = Mesh<string>("C");
}

// Constructor from option type
BaseMatrix::BaseMatrix(const vector<string>& optType0)
{
	param["r"] = Mesh(0.03);
	optType = optType0;
}

// Constructor from parameters and option type
BaseMatrix::BaseMatrix(const vectorMap& param0, const vector<string>& optType0)
{
	param = param0;
	optType = optType0;
}

// Destructor
BaseMatrix::~BaseMatrix()
{

}

// selector functions
// get all double-type parameters
const vectorMap& BaseMatrix::getParam() const
{
	return param;
}

// get specific parameter
const vector<double>& BaseMatrix::getParam(string paramName) const
{
	return param.at(paramName);
}

// get option type
const vector<string>& BaseMatrix::getType() const
{
	return optType;
}

// modifier functions
// input all double-type parameters
void BaseMatrix::setParam(const vectorMap& param0)
{
	param = param0;
}

// set specific parameter
void BaseMatrix::setParam(string paramName, const vector<double>& paramVec)
{
	param[paramName] = paramVec;
}

// set specific parameter to a constant
void BaseMatrix::setParam(string paramName, double a)
{
	param[paramName] = Mesh(a);
}

// set specific parameter to vary
void BaseMatrix::setParam(string paramName, double a, double b, double h)
{
	param[paramName] = Mesh(a, b, h);
}

// set option type to a constant type
void BaseMatrix::setType(string type0)
{
	optType = Mesh(type0);
}

// set option type to vary
void BaseMatrix::setType(const vector<string>& typeVec)
{
	optType = typeVec;
}

// switch option type
void BaseMatrix::toggle()
{
	for (unsigned int j = 0; j < optType.size(); j++)
	{
		if (optType[j] == "C")
			optType[j] = "P";
		else
			optType[j] = "C";
	}
}

// overloaded = operator
BaseMatrix& BaseMatrix::operator = (const BaseMatrix& source)
{
	if (this != &source)	// precludes self-assignment
	{
		param = source.param;
		optType = source.optType;
	}

	return *this;
}

// overloaded [] operator for writing
vector<double>& BaseMatrix::operator [] (string paramName)
{
	return param[paramName];
}

// overloaded [] operator for reading
const vector<double>& BaseMatrix::operator [] (string paramName) const
{
	return param.at(paramName);
}

// finds the size of the longest parameter vector
unsigned int BaseMatrix::maxSize() const
{
	vector<unsigned int> paramSizeVec;	// a vector to hold sizes of all paramter vectors

	vectorMap::const_iterator iter;
	for (iter = param.begin(); iter != param.end(); ++iter)
	{
		paramSizeVec.push_back(iter->second.size());	// adds each size to paramSizeVec
	}

	return *max_element(paramSizeVec.begin(), paramSizeVec.end());	// finds and returns the largest size
}

// sets specific paramter vector to a given size
void BaseMatrix::updateParam(string paramName, unsigned int maxSize0)
{
	unsigned int oldSize = param.at(paramName).size();	// gets the current size of target parameter

	if (oldSize < maxSize0)	// do nothing if current size is same as maxSize0; it should not be larger
	{
		if (oldSize == 1)
		{
			// when there was only one member, simply make a longer vector with constant value
			param.at(paramName) = vector<double>(maxSize0, param.at(paramName)[0]);
		}
		else
		{
			// when it was a mesh, extend the mesh while keeping the distance between mesh points same as before
			double h = param.at(paramName)[oldSize - 1] - param.at(paramName)[oldSize - 2]; // find distance between mesh points
			double lastElement = param.at(paramName).back();
			for (unsigned int j = oldSize; j < maxSize0; j++)
			{
				lastElement += h;	// new mesh point
				param.at(paramName).push_back(lastElement);	// add new mesh point
			}
		}
	}
}

// sets option type vector to a given size
void BaseMatrix::updateType(unsigned int maxSize0)
{
	// applies same logic as the previous function
	unsigned int oldSize = optType.size();

	if (oldSize < maxSize0)
	{
		if (oldSize == 1)
		{
			optType = vector<string>(maxSize0, optType[0]);
		}
		else
		{
			string lastElement = optType.back();
			for (unsigned int j = oldSize; j < maxSize0; j++)
			{
				optType.push_back(lastElement);	// repeats the last element until size is right
			}
		}
	}
}

// updates size of all parameter vectors
// the goal is to make sure all input vectors have the same size
void BaseMatrix::updateMatrix()
{
	unsigned int maxSize0 = maxSize();	// find the size of the currrently longest vector

	vectorMap::const_iterator iter;
	for (iter = param.begin(); iter != param.end(); ++iter)	// iterate through all paramters
	{
		updateParam(iter->first, maxSize0);	// set their size to the largest size
	}

	updateType(maxSize0);	// do the same to option type vector
}
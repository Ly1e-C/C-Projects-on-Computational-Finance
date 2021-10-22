// File name: PAmericanMatrix.cpp
// Author: Li Jin Chen
// Exercise: 9.Group_B
// Description: Source file for the PAmericanMatrix class. This is a derived class from BaseMatrix, used for 
//		calling the appropriate PAmericanOption functions for calculating option call and put prices. 


#include "PAmericanMatrix.hpp"
#include <cmath>
#include <sstream>
#include <algorithm>

// Default constructor
PAmericanMatrix::PAmericanMatrix() : BaseMatrix()
{
	// initializes paramters for a perpetual American matrix; risk-free rate already initialized in BaseMatrix. 
	// uses setParam() because derived class has no direct access to BaseMatrix's private member
	setParam("S", 100.0);
	setParam("sig", 0.2);
	setParam("K", 110.0);
	setParam("b", 0.0);
}

// Copy constructor
PAmericanMatrix::PAmericanMatrix(const PAmericanMatrix& source) : BaseMatrix(source)
{
	// empty because PAmericanMatrix has no new data member
}

// Constructor from paramters
PAmericanMatrix::PAmericanMatrix(const vectorMap& param0) : BaseMatrix(param0)
{

}

// Constructor from option type
PAmericanMatrix::PAmericanMatrix(const vector<string>& optType0) : BaseMatrix(optType0)
{
	// need to initialize paramters not initialized through BaseMatrix
	setParam("S", 100.0);
	setParam("sig", 0.2);
	setParam("K", 110.0);
	setParam("b", 0.0);
}

// Constructor from paramters and option type
PAmericanMatrix::PAmericanMatrix(const vectorMap& param0, const vector<string>& optType0) : BaseMatrix(param0, optType0)
{

}

// Destructor
PAmericanMatrix::~PAmericanMatrix()
{

}

// overloaded = operator
PAmericanMatrix& PAmericanMatrix::operator = (const PAmericanMatrix& source)
{
	if (this != &source)	// precludes self-assignment
		BaseMatrix::operator = (source);
	return *this;
}

// calculates option prices for the whole matrix
vector<double> PAmericanMatrix::getPrice() const
{
	unsigned int maxSize0 = maxSize();	// find the size of parameter vectors
	vector<double> result(maxSize0, 0.0);	// create a vector to hold resulting prices
	PAmericanOption tmp;	// create an instance of PAmericanOption
	
	vectorMap::const_iterator iter;
	for (unsigned int j = 0; j < maxSize0; j++)	// loop through each option
	{
		for (iter = getParam().begin(); iter != getParam().end(); ++iter)	// loop through each parameter
		{
			tmp.setParam(iter->first, getParam().at(iter->first)[j]);	// set PAmericanOption instance's inputs
		}
		tmp.setType(getType()[j]);	// set PAmericanOption instance's option type
		
		result[j] = tmp.Price();	// get option price
	}

	return result;
}
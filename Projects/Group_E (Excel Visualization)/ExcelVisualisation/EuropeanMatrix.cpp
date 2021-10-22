// File name: EuropeanMatrix.cpp
// Author: Li Jin Chen
// Exercise: 9.Group_E
// Description: Source file for the EuropeanMatrix class. This is a derived class from BaseMatrix, used for 
//		calling the appropriate EuropeanOption functions for calculating option prices and sensitivities. 


#include "EuropeanMatrix.hpp"
#include <cmath>
#include <sstream>
#include <algorithm>

// Default constructor
EuropeanMatrix::EuropeanMatrix() : BaseMatrix()
{
	// initializes paramters for an European option matrix; risk-free rate already initialized in BaseMatrix.
	// uses setParam() because derived class has no direct access to BaseMatrix's private member
	setParam("S", 100.0);
	setParam("sig", 0.2);
	setParam("K", 110.0);
	setParam("T", 0.5);
	setParam("b", getParam("r"));
}

// Copy constructor
EuropeanMatrix::EuropeanMatrix(const EuropeanMatrix& source) : BaseMatrix(source)
{
	// empty because EuropeanMatrix has no new data member
}

// Constructor from paramters
EuropeanMatrix::EuropeanMatrix(const vectorMap& param0) : BaseMatrix(param0)
{

}

// Constructor from option type
EuropeanMatrix::EuropeanMatrix(const vector<string>& optType0) : BaseMatrix(optType0)
{
	// need to initialize paramters not initialized through BaseMatrix
	setParam("S", 100.0);
	setParam("sig", 0.2);
	setParam("K", 110.0);
	setParam("T", 0.5);
	setParam("b", getParam("r"));
}

// Constructor from paramters and option type
EuropeanMatrix::EuropeanMatrix(const vectorMap& param0, const vector<string>& optType0) : BaseMatrix(param0, optType0)
{

}

// Destructor
EuropeanMatrix::~EuropeanMatrix()
{

}

// overloaded = operator
EuropeanMatrix& EuropeanMatrix::operator = (const EuropeanMatrix& source)
{
	if (this != &source)	// precludes self-assignment
		BaseMatrix::operator = (source);
	return *this;
}

// calculates option prices for the whole matrix
vector<double> EuropeanMatrix::getPrice() const
{
	unsigned int maxSize0 = maxSize();	// find the size of parameter vectors
	vector<double> result(maxSize0, 0.0);	// create a vector to hold resulting prices
	EuropeanOption tmp;	// create an instance of EuropeanOption

	vectorMap::const_iterator iter;
	for (unsigned int j = 0; j < maxSize0; j++)	// loop through each option
	{
		for (iter = getParam().begin(); iter != getParam().end(); ++iter)	// loop through each parameter
		{
			tmp.setParam(iter->first, getParam().at(iter->first)[j]);	// set EuropeanOption instance's inputs
		}
		tmp.setType(getType()[j]);	// set EuropeanOption instance's option type

		result[j] = tmp.Price();	// get option price
	}

	return result;
}

// calculates option delta for the whole matrix
vector<double> EuropeanMatrix::getDelta() const
{
	// same logic applies from getPrice() function
	unsigned int maxSize0 = maxSize();
	vector<double> result(maxSize0, 0.0);
	EuropeanOption tmp;

	vectorMap::const_iterator iter;
	for (unsigned int j = 0; j < maxSize0; j++)
	{
		for (iter = getParam().begin(); iter != getParam().end(); ++iter)
		{
			tmp.setParam(iter->first, getParam().at(iter->first)[j]);
		}
		tmp.setType(getType()[j]);

		result[j] = tmp.Delta();	// get option delta
	}

	return result;
}

// calculates option gamma for the whole matrix
vector<double> EuropeanMatrix::getGamma() const
{
	// same logic applies from getPrice() function
	unsigned int maxSize0 = maxSize();
	vector<double> result(maxSize0, 0.0);
	EuropeanOption tmp;

	vectorMap::const_iterator iter;
	for (unsigned int j = 0; j < maxSize0; j++)
	{
		for (iter = getParam().begin(); iter != getParam().end(); ++iter)
		{
			tmp.setParam(iter->first, getParam().at(iter->first)[j]);
		}

		result[j] = tmp.Gamma();	// get option gamma
	}

	return result;
}

// get option price, delta, and gamma and outputs a map of vectors
vectorMap EuropeanMatrix::getAll() const
{
	vectorMap result;
	result["Price"] = getPrice();
	result["Delta"] = getDelta();
	result["Gamma"] = getGamma();
	return result;
}

// calculates delta using divided differences
vector<double> EuropeanMatrix::getddDelta(double h) const
{
	// same logic applies from getPrice() function
	unsigned int maxSize0 = maxSize();
	vector<double> result(maxSize0, 0.0);
	EuropeanOption tmp;

	vectorMap::const_iterator iter;
	for (unsigned int j = 0; j < maxSize0; j++)
	{
		for (iter = getParam().begin(); iter != getParam().end(); ++iter)
		{
			tmp.setParam(iter->first, getParam().at(iter->first)[j]);
		}
		tmp.setType(getType()[j]);

		result[j] = ddDelta(tmp, h);	// get delta using divided differences
	}

	return result;
}

// calculates gamma using divided differences
vector<double> EuropeanMatrix::getddGamma(double h) const
{
	// same logic applies from getPrice() function
	unsigned int maxSize0 = maxSize();
	vector<double> result(maxSize0, 0.0);
	EuropeanOption tmp;

	vectorMap::const_iterator iter;
	for (unsigned int j = 0; j < maxSize0; j++)
	{
		for (iter = getParam().begin(); iter != getParam().end(); ++iter)
		{
			tmp.setParam(iter->first, getParam().at(iter->first)[j]);
		}

		result[j] = ddGamma(tmp, h);	// get delta using divided differences
	}

	return result;
}
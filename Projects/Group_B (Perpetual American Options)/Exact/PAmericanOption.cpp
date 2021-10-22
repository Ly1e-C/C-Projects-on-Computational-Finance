// File name: PAmericanOption.cpp
// Author: Li Jin Chen
// Exercise: 9.Group_B
// Description: Source file for the PAmericanOption class. This is a derived class from BaseOption, used for 
//		calculating call and put price of perpetual American options. 


#include "PAmericanOption.hpp"
#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <iostream>
using namespace boost::math;

// for convenience and readability
#define S getParam("S")
#define r getParam("r")
#define sig getParam("sig")
#define K getParam("K")
#define b getParam("b")

// calculates call price
double PAmericanOption::CallPrice() const
{
	double sig2 = sig * sig;
	double fac = b / sig2 - 0.5;
	fac *= fac;
	double y1 = 0.5 - b / sig2 + sqrt(fac + 2.0 * r / sig2);

	if (1.0 == y1)
		return S;

	double fac2 = ((y1 - 1.0) * S) / (y1 * K);
	double c = K * pow(fac2, y1) / (y1 - 1.0);

	return c;
}

// calculates put price
double PAmericanOption::PutPrice() const
{
	double sig2 = sig * sig;
	double fac = b / sig2 - 0.5;
	fac *= fac;
	double y2 = 0.5 - b / sig2 - sqrt(fac + 2.0 * r / sig2);

	if (0.0 == y2)
		return S;

	double fac2 = ((y2 - 1.0) * S) / (y2 * K);
	double p = K * pow(fac2, y2) / (1.0 - y2);

	return p;
}

// Default constructor
PAmericanOption::PAmericanOption() : BaseOption()
{
	// initializes paramters for a perpetural American option; risk-free rate already initialized in BaseOption
	// uses setParam() because derived class has no direct access to BaseOption's private member
	setParam("S", 100.0);
	setParam("sig", 0.2);
	setParam("K", 110.0);
	setParam("b", 0.0);
}

// Copy constructor
PAmericanOption::PAmericanOption(const PAmericanOption& o2) : BaseOption(o2)
{
	// empty because PAmericanOption has no new data member
}

// Constructor from paramters
PAmericanOption::PAmericanOption(const doubleMap& param0) : BaseOption(param0)
{

}

// Constructor from option type
PAmericanOption::PAmericanOption(string optionType) : BaseOption(optionType)
{
	// need to initialize paramters not initialized through BaseOption
	setParam("S", 100.0);
	setParam("sig", 0.2);
	setParam("K", 110.0);
	setParam("b", 0.0);
}

// Constructor from paramters and option type
PAmericanOption::PAmericanOption(const doubleMap& param0, string optionType) : BaseOption(param0, optionType)
{

}

// Destructor
PAmericanOption::~PAmericanOption()
{

}

// overloaded = operator
PAmericanOption& PAmericanOption::operator = (const PAmericanOption& option2)
{
	if (this != &option2)
		BaseOption::operator = (option2);
	return *this;
}

// gets the proper price based on option type
double PAmericanOption::Price() const
{
	if (getType() == "C")
		return CallPrice();
	else
		return PutPrice();
}
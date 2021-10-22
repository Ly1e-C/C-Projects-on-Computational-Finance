// File name: DividedDifferences.hpp
// Author: Li Jin Chen
// Exercise: 9.Group_E
// Description: This includes functions for calculating delta and gamma using divided differences. 


#ifndef DividedDifferences_HPP
#define DividedDifferences_HPP

#include <cmath>
using namespace std;

// calculates delta using divided differences
template <typename T>
inline double ddDelta(T& opt0, double h)
{
	double oldS = opt0.getParam("S");	// records the original S
	opt0.setParam("S", oldS + h);	// change S slightly
	double pPlus = opt0.Price();	// find new price
	opt0.setParam("S", oldS - h);
	double pMinus = opt0.Price();
	opt0.setParam("S", oldS);	// resets S to original value
	return (pPlus - pMinus) / (2 * h);	// dd formula for delta
}

// calculates gamma using divided differences
template <typename T>
inline double ddGamma(T& opt0, double h)
{
	double p0 = opt0.Price();
	double oldS = opt0.getParam("S");
	opt0.setParam("S", oldS + h);
	double pPlus = opt0.Price();
	opt0.setParam("S", oldS - h);
	double pMinus = opt0.Price();
	opt0.setParam("S", oldS);
	return (pPlus - 2 * p0 + pMinus) / (pow(h, 2));	// dd formula
}

#endif
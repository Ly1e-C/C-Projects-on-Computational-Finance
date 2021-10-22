// File name: EuropeanMatrix.hpp
// Author: Li Jin Chen
// Exercise: 9.Group_A
// Description: Header file for the EuropeanMatrix class. This is a derived class from BaseMatrix, used for 
//		calling the appropriate EuropeanOption functions for calculating option prices and sensitivities. 


#ifndef EuropeanMatrix_HPP
#define EuropeanMatrix_HPP

#include "Mesher.hpp"
#include "DividedDifferences.hpp"
#include "EuropeanOption.hpp"
#include "BaseMatrix.hpp"
#include <vector>
#include <map>
#include <iostream>
using namespace std;

typedef map<string, vector<double>> vectorMap;	// for convenience and readability

class EuropeanMatrix : public BaseMatrix
{
	// no new data member

public:
	EuropeanMatrix();	// Default constructor
	EuropeanMatrix(const EuropeanMatrix& source);	// Copy constructor
	EuropeanMatrix(const vectorMap& param0);	// Constructor from paramters
	EuropeanMatrix(const vector<string>& optType0);	// Constructor from option type
	EuropeanMatrix(const vectorMap& param0, const vector<string>& optType0);	// Constructor from paramters and option type
	virtual ~EuropeanMatrix();	// Destructor

	// overloaded = operator
	EuropeanMatrix& operator = (const EuropeanMatrix& source);

	// functions that calculate option price and sensitivities
	vector<double> getPrice() const;
	vector<double> getDelta() const;
	vector<double> getGamma() const;
	vectorMap getAll() const;

	// functions that calculate delta and gamma using divided differences
	vector<double> getddDelta(double h) const;
	vector<double> getddGamma(double h) const;
};

#endif
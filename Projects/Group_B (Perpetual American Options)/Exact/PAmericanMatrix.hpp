// File name: PAmericanMatrix.hpp
// Author: Li Jin Chen
// Exercise: 9.Group_B
// Description: Header file for the PAmericanMatrix class. This is a derived class from BaseMatrix, used for 
//		calling the appropriate PAmericanOption functions for calculating option call and put prices. 


#ifndef PAmericanMatrix_HPP
#define PAmericanMatrix_HPP

#include "Mesher.hpp"
#include "PAmericanOption.hpp"
#include "BaseMatrix.hpp"
#include <vector>
#include <map>
#include <iostream>
using namespace std;

typedef map<string, vector<double>> vectorMap;	// for convenience and readability

class PAmericanMatrix : public BaseMatrix
{
	// no new data member

public:
	PAmericanMatrix();	// Default constructor
	PAmericanMatrix(const PAmericanMatrix& source);	// Copy constructor
	PAmericanMatrix(const vectorMap& param0);	// Constructor from paramters
	PAmericanMatrix(const vector<string>& optType0);	// Constructor from option type
	PAmericanMatrix(const vectorMap& param0, const vector<string>& optType0);	// Constructor from paramters and option type
	virtual ~PAmericanMatrix();	// Destructor

	// overloaded = operator
	PAmericanMatrix& operator = (const PAmericanMatrix& source);

	// calculates option price
	vector<double> getPrice() const;
};

#endif
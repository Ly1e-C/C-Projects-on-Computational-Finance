// File name: BaseMatrix.hpp
// Author: Li Jin Chen
// Exercise: 9.Group_A
// Description: Header file for the BaseMatrix class. It is the abstract class from which the EuropeanMatrix 
//		class and the PAmericanMatrix class are derived. It includes functionalities for setting and getting 
//		parameters. It also makes sure that all parameters are vectors of the same size. Calculations are 
//		delagated to derived classes. 


#ifndef BaseMatrix_HPP
#define BaseMatrix_HPP

#include "Mesher.hpp"
#include <vector>
#include <map>
#include <iostream>
using namespace std;

typedef map<string, vector<double>> vectorMap;	// for convenience and readability

class BaseMatrix
{
private:
	// data members
	vectorMap param;	// a map that can hold all possible double-type parameters
	vector<string> optType;	// option type: "C" or "P"; now a vector to allow varying option type within matrix

public:
	BaseMatrix();	// Default constructor
	BaseMatrix(const BaseMatrix& source);	// Copy constructor
	BaseMatrix(const vectorMap& param0);	// Constructor from parameters
	BaseMatrix(const vector<string>& optType0);	// Constructor from option type
	BaseMatrix(const vectorMap& param0, const vector<string>& optType0);	// Constructor from parameters and option type
	virtual ~BaseMatrix();	// Destructor

	// selector functions
	const vectorMap& getParam() const;	// get all double-type parameters
	const vector<double>& getParam(string paramName) const;	// get specific parameter
	const vector<string>& getType() const;	// get option type

	// modifier functions
	void setParam(const vectorMap& param0);	// input all double-type parameters
	void setParam(string paramName, const vector<double>& paramVec); // set specific parameter
	void setParam(string paramName, double a); // set specific parameter to a constant
	void setParam(string paramName, double a, double b, double h); // set specific parameter to vary
	void setType(string type0);	// set option type to a constant type
	void setType(const vector<string>& typeVec);	// set option type to vary
	void toggle();	// switch option type

	// overloaded = and [] operators
	BaseMatrix& operator = (const BaseMatrix& source);
	vector<double>& operator [] (string paramName);
	const vector<double>& operator [] (string paramName) const;

	// finds the size of the longest parameter vector
	unsigned int maxSize() const;

	// sets specific paramter vector to a given size
	void updateParam(string paramName, unsigned int maxSize0);

	// sets option type vector to a given size
	void updateType(unsigned int maxSize0);

	// updates size of all parameter vectors
	void updateMatrix();

	// pure virtual function, overridden by all derived classes
	virtual vector<double> getPrice() const = 0;
};

#endif
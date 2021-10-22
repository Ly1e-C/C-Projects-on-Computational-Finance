// File name: BaseOption.hpp
// Author: Li Jin Chen
// Exercise: 9.Group_A
// Description: Header file for the BaseOption class. It is the abstract class from which the EuropeanOption 
//		class and the PAmericanOption class are derived. It includes functionalities for setting and getting 
//		parameters. Calculations are delagated to derived classes. 


#ifndef BaseOption_hpp
#define BaseOption_hpp

#include <string>
#include <vector>
#include <map>
using namespace std;

typedef map<string, double> doubleMap;	// for convenience and readability

class BaseOption
{
private:
	// data members
	doubleMap param;	// a map that can hold all possible double-type parameters
	string optType;	// option type: "C" or "P"

	// private functions
	void init();	// initialises default values
	void copy(const BaseOption& o2);	// copies parameter values

public:
	BaseOption();	// Default constructor
	BaseOption(const BaseOption& option2);	// Copy constructor
	BaseOption(const doubleMap& param0);	// Constructor from parameters
	BaseOption(string optionType);	// Constructor from option type
	BaseOption(const doubleMap& param0, string optionType);	// Constructor from parameters and option type
	virtual ~BaseOption();	// Destructor

	// selector functions
	const doubleMap& getParam() const;	// get all double-type parameters
	double getParam(string paramName) const;	// get specific parameter
	string getType() const;	// get option type

	// modifier functions
	void setParam(const doubleMap& param0);	// input all double-type parameters
	void setParam(string paramName, double newVal); // set specific parameter
	void setType(string newType);	// set option type
	void toggle();		// switch option type

	// overloaded = and [] operators
	BaseOption& operator = (const BaseOption& option2);
	double& operator [] (string paramName);
	const double& operator [] (string paramName) const;

	// pure virtual function, overridden by all derived classes
	virtual double Price() const = 0;
};

#endif
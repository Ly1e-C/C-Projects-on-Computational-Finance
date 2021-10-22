// File name: PAmericanOption.hpp
// Author: Li Jin Chen
// Exercise: 9.Group_B
// Description: Header file for the PAmericanOption class. This is a derived class from BaseOption, used for 
//		calculating call and put price of perpetual American options. 


#ifndef PAmericanOption_hpp
#define PAmericanOption_hpp

#include "BaseOption.hpp"
#include <string>
using namespace std;

typedef map<string, double> doubleMap;

class PAmericanOption : public BaseOption
{
private:	// no new data member
	// 'Kernel' functions for option calculations
	double CallPrice() const;
	double PutPrice() const;

public:	// Public functions
	PAmericanOption();	// Default constructor
	PAmericanOption(const PAmericanOption& option2);	// Copy constructor
	PAmericanOption(const doubleMap& param0);	// Constructor from paramters
	PAmericanOption(string optionType);	// Constructor from option type
	PAmericanOption(const doubleMap& param0, string optionType);	// Constructor from paramters and option type
	virtual ~PAmericanOption();	// Destructor

	// overloaded = operator
	PAmericanOption& operator = (const PAmericanOption& option2);

	// calculates option price
	double Price() const;
};

#endif
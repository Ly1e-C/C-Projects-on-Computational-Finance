// File name: EuropeanOption.hpp
// Author: Li Jin Chen
// Exercise: 9.Group_E
// Description: Header file for the EuropeanOption class. This is a derived class from BaseOption, used for 
//		calculating option prices, delta, and gamma through Black-Scholes. It also includes functionalities 
//		for checking put-call parity. 


#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp

#include "BaseOption.hpp"
#include <string>
using namespace std;

typedef map<string, double> doubleMap;

class EuropeanOption : public BaseOption
{
private:	// no new data member
	// Gaussian functions
	double n(double x) const;
	double N(double x) const;

	// 'Kernel' functions for option calculations
	double CallPrice() const;
	double PutPrice() const;
	double CallDelta() const;
	double PutDelta() const;
	double CallParity(double pPrice) const;	// calculates call price through put-call parity
	double PutParity(double cPrice) const;	// calculates put price through put-call parity

public:
	EuropeanOption();	// Default constructor
	EuropeanOption(const EuropeanOption& option2);	// Copy constructor
	EuropeanOption(const doubleMap& param0);	// Constructor from paramters
	EuropeanOption(string optionType);	// Constructor from option type
	EuropeanOption(const doubleMap& param0, string optionType);	// Constructor from paramters and option type
	virtual ~EuropeanOption();	// Destructor

	// overloaded = operator
	EuropeanOption& operator = (const EuropeanOption& option2);

	// functions that calculate option price and sensitivities
	double Price() const;
	double Delta() const;
	double Gamma() const;

	// functions related tp using put-call parity
	double ParityPrice() const;
	double ParityPrice(double val) const;
	bool Parity() const;	// calculate both call and put prices then check if parity holds
	bool Parity(double cPrice, double pPrice) const; // use prices given to check if parity holds
};

#endif
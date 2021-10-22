// File name: EuropeanOption.cpp
// Author: Li Jin Chen
// Exercise: 9.Group_A
// Description: Source file for the EuropeanOption class. This is a derived class from BaseOption, used for 
//		calculating option prices, delta, and gamma through Black-Scholes. It also includes functionalities 
//		for checking put-call parity. 


#include "EuropeanOption.hpp"
#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <iostream>
using namespace boost::math;

// for convenience and readability
#define S getParam("S")
#define r getParam("r")
#define sig getParam("sig")
#define K getParam("K")
#define T getParam("T")
#define b getParam("b")

// pdf function
double EuropeanOption::n(double x) const
{
	normal_distribution<> stdNormal(0.0, 1.0);	// using boost package
	return pdf(stdNormal, x);
}

// cdf function
double EuropeanOption::N(double x) const
{
	normal_distribution<> stdNormal(0.0, 1.0);	// using boost package
	return cdf(stdNormal, x);
}

// 'Kernel' functions for option calculations
// calculates call price
double EuropeanOption::CallPrice() const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return (S * exp((b - r) * T) * N(d1)) - (K * exp(-r * T) * N(d2));
}

// calculates put price
double EuropeanOption::PutPrice() const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return (K * exp(-r * T) * N(-d2)) - (S * exp((b - r) * T) * N(-d1));
}

// calculates call delta
double EuropeanOption::CallDelta() const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;

	return exp((b - r) * T) * N(d1);
}

// calculates put delta
double EuropeanOption::PutDelta() const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;

	return exp((b - r) * T) * (N(d1) - 1.0);
}

// calculates call price through put-call parity
double EuropeanOption::CallParity(double pPrice) const	// with put price as input
{
	return pPrice + S - K * exp(-r * T);
}

// calculates put price through put-call parity
double EuropeanOption::PutParity(double cPrice) const	// with call price as input
{
	return cPrice + K * exp(-r * T) - S;
}

// Default constructor
EuropeanOption::EuropeanOption() : BaseOption()
{
	// initializes paramters for an European option; risk-free rate already initialized in BaseOption
	// uses setParam() because derived class has no direct access to BaseOption's private member
	setParam("S", 100.0);
	setParam("sig", 0.2);
	setParam("K", 110.0);
	setParam("T", 0.5);
	setParam("b", r);	// Black and Scholes stock option model (1973)
}

// Copy constructor
EuropeanOption::EuropeanOption(const EuropeanOption& o2) : BaseOption(o2)
{
	// empty because EuropeanOption has no new data member
}

// Constructor from paramters
EuropeanOption::EuropeanOption(const doubleMap& param0) : BaseOption(param0)
{

}

// Constructor from option type
EuropeanOption::EuropeanOption(string optionType) : BaseOption(optionType)
{	
	// need to initialize paramters not initialized through BaseOption
	setParam("S", 100.0);
	setParam("sig", 0.2);
	setParam("K", 110.0);
	setParam("T", 0.5);
	setParam("b", r);	// Black and Scholes stock option model (1973)
}

// Constructor from paramters and option type
EuropeanOption::EuropeanOption(const doubleMap& param0, string optionType) : BaseOption(param0, optionType)
{

}

// Destructor
EuropeanOption::~EuropeanOption()
{

}

// overloaded = operator
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2)
{
	if (this != &option2)
		BaseOption::operator = (option2);
	return *this;
}

// functions that calculate option price and sensitivities
// gets the proper price based on option type
double EuropeanOption::Price() const
{
	// uses getType() because derived class has no direct access to BaseOption's private member
	if (getType() == "C")
		return CallPrice();
	else
		return PutPrice();
}

// gets the proper delta based on option type
double EuropeanOption::Delta() const
{
	if (getType() == "C")
		return CallDelta();
	else
		return PutDelta();
}

// calculates option gamma; same for both call and put
double EuropeanOption::Gamma() const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;

	return n(d1) * exp((b - r) * T) / (S * tmp);
}

// functions related tp using put-call parity
// for call option: gets call price, then gets put price from put-call parity
// for put option: gets put price, then gets call price from put-call parity
double EuropeanOption::ParityPrice() const
{
	if (getType() == "C")
	{
		cout << "Put price from parity: \n";
		return PutParity(CallPrice());
	}
	else
	{
		cout << "Call price from parity: \n";
		return CallParity(PutPrice());
	}
}

// for call option: takes input as call price, then gets put price from put-call parity
// for put option: takes input as put price, then gets call price from put-call parity
double EuropeanOption::ParityPrice(double val) const
{
	if (getType() == "C")
	{
		cout << "Put price from parity: \n";
		return PutParity(val);
	}
	else
	{
		cout << "Call price from parity: \n";
		return CallParity(val);
	}
}

// calculate both call and put prices then check if parity holds
bool EuropeanOption::Parity() const
{
	// includes a tolerance of 0.00001
	if (abs((CallPrice() + K * exp(-r * T)) - (S + PutPrice())) < 0.00001)
	{
		cout << "Put-call parity holds\n";
		return true;
	}
	else
	{
		cout << "Put-call parity does not hold\n";
		return false;
	}
}

// use prices given to check if parity holds
bool EuropeanOption::Parity(double cPrice, double pPrice) const
{
	// includes a tolerance of 0.00001
	if (abs((cPrice + K * exp(-r * T)) - (S + pPrice)) < 0.00001)
	{
		cout << "Put-call parity holds\n";
		return true;
	}
	else
	{
		cout << "Put-call parity does not hold\n";
		return false;
	}
}
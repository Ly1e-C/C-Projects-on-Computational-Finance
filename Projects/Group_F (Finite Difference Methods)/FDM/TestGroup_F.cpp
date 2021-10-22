// File name: TestGroup_F.cpp
// Author: Li Jin Chen
// Exercise: 9.Group_F
// Description: This is an alternative to the TestBSPDE1.cpp test file. Instead of testing one N value at 
//		a time and outputting results to Excel, this looks for the smallest N that would give reasonable 
//		(stable) price results given a certain J/K ratio. It uses a simple grid search, starting from a 
//		large N value and looping to a small enough N value to not give reasonable price results. 


#include "FdmDirector.hpp"

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include "UtilitiesDJD/ExcelDriver/ExcelDriverLite.hpp"

namespace BS // Black Scholes
{
	// Test batch
	double T = 0.25;
	double K = 65;
	double sig = 0.30;
	double r = 0.08;
	double D = 0.0; // aka q

	//// Batch 1
	//double T = 0.25;
	//double K = 65;
	//double sig = 0.30;
	//double r = 0.08;
	//double D = 0.0; // aka q

	//// Batch 2
	//double T = 1.0;
	//double K = 100;
	//double sig = 0.2;
	//double r = 0.0;
	//double D = 0.0; // aka q

	//// Batch 3
	//double T = 1.0;
	//double K = 10;
	//double sig = 0.50;
	//double r = 0.12;
	//double D = 0.0; // aka q

	//// Batch 4
	//double T = 30.0;
	//double K = 100.0;
	//double sig = 0.30;
	//double r = 0.08;
	//double D = 0.0; // aka q

	double mySigma(double x, double t)
	{

		double sigmaS = sig * sig;

		return 0.5 * sigmaS * x * x;
	}

	double myMu(double x, double t)
	{

		return (r - D) * x;

	}

	double myB(double x, double t)
	{

		return  -r;
	}

	double myF(double x, double t)
	{
		return 0.0;
	}

	double myBCL(double t)
	{
		// Put
		return K * exp(-r * t);
	}

	double myBCR(double t)
	{

		// Put
		return 0.0; // P
	}

	double myIC(double x)
	{ // Payoff 

		// Put
		return max(K - x, 0.0);
	}

}


int main()
{
	using namespace ParabolicIBVP;

	// Assignment of functions
	sigma = BS::mySigma;
	mu = BS::myMu;
	b = BS::myB;
	f = BS::myF;
	BCL = BS::myBCL;
	BCR = BS::myBCR;
	IC = BS::myIC;

	double JoverK = 5;	// the ratio J/K, used for setting mesh size in space (price)
	int J = static_cast<int>(JoverK * BS::K);
	int N = 10000;	// initial N value, used for setting mesh size in time

	double Smax = 5 * BS::K;			// Magix

	double threshold = BS::K;	// used as a criterion for determining if FDM result is resonable
	int smallestN;	// used to hold the smallest stable N
	int interval = 100;	// step size for the grid search for N; useful when far away from target N
	bool foundN = false;	// used for tracking if the smallest stable N is found
	
	// a loop to find the smallest N that would give reasonable FDM result
	while (!foundN)	// run while smallest stable N is not yet found
	{
		cout << "N is now " << N << endl;	// shows progress

		FDMDirector fdir(Smax, BS::T, J, N);

		fdir.doit();

		vector<double>::const_iterator iter = fdir.current().begin();
		while (iter != fdir.current().end() && !foundN)	// loop through each calculated price
		{
			// check each calculated price for three criteria: 
			// 1) it should not be greater than strike price for a put option
			// 2) it should not be negative
			// 3) it should not be NAN
			// though these are rough criteria, they are useful even when true prices are not known
			if (*iter > threshold || *iter < -0.01 || isnan(*iter))
			{
				// if any criterion is not met, then previous N is the smallest stable N
				smallestN = N + interval;
				foundN = true;	// used for ending the loop
			}
			iter++;
		}

		N -= interval;	// decrement N by interval
	}
	
	// display findings
	cout << "\nJ = " << J << endl;
	cout << "N = " << smallestN << endl;
	cout << "h = " << Smax / (double)J << endl;
	cout << "k = " << BS::T / (double)smallestN << endl;

	return 0;
}
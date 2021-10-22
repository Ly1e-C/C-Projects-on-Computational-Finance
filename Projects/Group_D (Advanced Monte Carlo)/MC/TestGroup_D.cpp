// File name: TestGroup_D.cpp
// Author: Li Jin Chen
// Exercise: 9.Group_D
// Description: This is a file for testing the use of Monte Carlo method in determining option prices. 
//		Here the CEV model with a choice of elasticity parameter and the Euler method are applied. We 
//		allow NT and NSIM to take on a set of values. 


#include "OptionData.hpp" 
#include "UtilitiesDJD/RNG/NormalGenerator.hpp"
#include "UtilitiesDJD/Geometry/Range.cpp"
#include <cmath>
#include <iostream>
using namespace std;

template <class T> void print(const std::vector<T>& myList)
{  // A generic print function for vectors

	cout << std::endl << "Size of vector is " << l.size() << "\n[";

	// We must use a const iterator here, otherwise we get a compiler error.
	std::vector<T>::const_iterator i;
	for (i = myList.begin(); i != myList.end(); ++i)
	{
		cout << *i << ",";

	}

	cout << "]\n";
}

namespace SDEDefinition
{ // Defines drift + diffusion + data

	OptionData* data;				// The data for the option MC

	double drift(double t, double X)
	{ // Drift term

		return (data->r) * X; // r - D
	}


	double diffusion(double t, double X)
	{ // Diffusion term

		double betaCEV = 1.0;
		return data->sig * pow(X, betaCEV);

	}

	double diffusionDerivative(double t, double X)
	{ // Diffusion term, needed for the Milstein method

		double betaCEV = 1.0;
		return 0.5 * (data->sig) * (betaCEV)*pow(X, 2.0 * betaCEV - 1.0);
	}
} // End of namespace

// calculates standard deviation
double getSD(const vector<double>& myVector, double r, double T)
{
	double iniVal = 0.0;
	double vecSum = accumulate(myVector.begin(), myVector.end(), iniVal);	// sum of simulated prices
	double vecSquSum = inner_product(myVector.begin(), myVector.end(), myVector.begin(), iniVal);	// sum of squard simulated prices
	double M = myVector.size();
	return sqrt((vecSquSum - pow(vecSum, 2) / M) / (M - 1)) * exp(-r * T);	// applies SD formula
}

// calculates standard error
double getSE(const vector<double>& myVector, double r, double T)
{
	double SD = getSD(myVector, r, T);
	double M = myVector.size();
	return SD / sqrt(M);	// applies 
}


int main()
{
	cout << "1 factor MC with explicit Euler\n";
	OptionData myOption;
	double S_0;
	int batchNum;	// identifier of the batch
	
	cout << "Select batch number (0-4): ";	// let user select one of the four test batches
	cin >> batchNum;

	switch (batchNum)	// set proper option parameters
	{
	case 0:
		myOption.T = 1.5;
		myOption.K = 120;
		myOption.sig = 0.40;
		myOption.r = 0.04;
		S_0 = 100;
		break;
	case 1:
		myOption.T = 0.25;
		myOption.K = 65;
		myOption.sig = 0.30;
		myOption.r = 0.08;
		S_0 = 60;
		break;
	case 2:
		myOption.T = 1.0;
		myOption.K = 100;
		myOption.sig = 0.2;
		myOption.r = 0.0;
		S_0 = 100;
		break;
	case 3:
		myOption.T = 1.0;
		myOption.K = 10;
		myOption.sig = 0.50;
		myOption.r = 0.12;
		S_0 = 5;
		break;
	case 4:
		myOption.T = 30.0;
		myOption.K = 100.0;
		myOption.sig = 0.30;
		myOption.r = 0.08;
		S_0 = 100.0;
		break;
	default:
		myOption.T = 0.25;
		myOption.K = 65;
		myOption.sig = 0.30;
		myOption.r = 0.08;
		S_0 = 60;
		break;
	}
	
	cout << "Enter 1 for Call or -1 for Put: ";	// let user choose either call or put
	cin >> myOption.type;	// Put -1, Call +1

	// NT and NSIM values for testing code (fast)
	vector<long> NTvec = { 300 };
	vector<long> NSIMvec = { 100000 };

	// NT and NSIM values for generating actual estimations (slow)
	//vector<long> NTvec = { 100, 200, 500, 1000 };
	//vector<long> NSIMvec = { 10000, 30000, 100000, 300000, 1000000, 3000000, 10000000 };

	vector<long>::const_iterator NTiter;	// for iterating through vector of NT values
	vector<long>::const_iterator NSIMiter;	// for iterating through vector of NSIM values

	cout << "\nMonte Carlo results: \n" << endl;

	clock_t startTime = clock();	// timer for keep tracking of simulation time

	for (NTiter = NTvec.begin(); NTiter != NTvec.end(); ++NTiter)	// loop through NT values
	{
		long N = *NTiter;

		for (NSIMiter = NSIMvec.begin(); NSIMiter != NSIMvec.end(); ++NSIMiter)	// loop through NSIM values
		{
			// Create the basic SDE (Context class)
			Range<double> range(0.0, myOption.T);
			double VOld = S_0;
			double VNew = 0.0;

			vector<double> x = range.mesh(N);

			// V2 mediator stuff
			long NSim = *NSIMiter;

			double k = myOption.T / double(N);
			double sqrk = sqrt(k);

			// Normal random number
			double dW;
			double price = 0.0;	// Option price

			// NormalGenerator is a base class
			NormalGenerator* myNormal = new BoostNormal();

			using namespace SDEDefinition;
			SDEDefinition::data = &myOption;

			vector<double> res;	// for keep tracking of simulated option payoffs
			int coun = 0; // Number of times S hits origin

			// A.
			for (long i = 1; i <= NSim; ++i)
			{ // Calculate a path at each iteration

				//if ((i / 1000000) * 1000000 == i)
				//{// Give status after each 1000th iteration

				//	cout << i << endl;
				//}

				VOld = S_0;
				for (unsigned long index = 1; index < x.size(); ++index)
				{

					// Create a random number
					dW = myNormal->getNormal();

					// The FDM (in this case explicit Euler)
					VNew = VOld + (k * drift(x[index - 1], VOld))
						+ (sqrk * diffusion(x[index - 1], VOld) * dW);

					VOld = VNew;

					// Spurious values
					if (VNew <= 0.0) coun++;
				}

				double tmp = myOption.myPayOffFunction(VNew);
				res.push_back(tmp);	// collects simulated option payoffs
				price += (tmp) / double(NSim);
			}

			// D. Finally, discounting the average price
			price *= exp(-myOption.r * myOption.T);

			// Cleanup; V2 use scoped pointer
			delete myNormal;

			double SDval = getSD(res, myOption.r, myOption.T);	// calculates standard deviation
			double SEval = getSE(res, myOption.r, myOption.T);	// calculates standard error

			cout << "NT: " << N << ", NSIM: " << NSim << endl;
			cout << "Price, after discounting: " << price << ", " << endl;
			cout << "Number of times origin is hit: " << coun << endl;
			cout << "Standard deviation(SD): " << SDval << endl;
			cout << "Standard error(SD): " << SEval << "\n" << endl;

			// for outputing results in a more tabulated format
			//string typeName;
			//if (myOption.type == 1)
			//	typeName = "Call";
			//else
			//	typeName = "Put";

			//cout << batchNum << "\t" << typeName << "\t" << N << "\t" << NSim << "\t" << price << "\t" << SDval << "\t" << SEval << endl;
		}
	}

	// displays simulation time
	clock_t endTime = clock();
	clock_t timeTaken = endTime - startTime;
	double timeInMinutes = timeTaken / (double)CLOCKS_PER_SEC / 60.0;
	cout << "Minutes Taken: " << timeInMinutes << endl;

	return 0;
}
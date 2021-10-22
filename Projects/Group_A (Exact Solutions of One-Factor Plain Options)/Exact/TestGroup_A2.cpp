

#include "Mesher.hpp"
#include "DividedDifferences.hpp"
#include "EuropeanOption.hpp"
#include "EuropeanMatrix.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
	double p1;
	double p2;

	// ============ Single option input ============

	EuropeanOption b1;
	b1.setParam("T", 1.5);	// enter the paramters
	b1.setParam("K", 120);
	b1.setParam("sig", 0.40);
	b1.setParam("r", 0.04);
	b1.setParam("S", 100);
	b1.setParam("b", 0.0);	// b = r
	
	cout << "Test Batch" << endl;
	b1.setType("C");	// set to call option
	p1 = b1.Price();	// get exact call price
	cout << "Call price: \n" << p1 << endl;
	cout << b1.ParityPrice(p1) << endl;	// find put price using call price and put-call parity
	cout << "Call delta: \n" << b1.Delta() << endl;	// get call delta
	cout << "Call delta (divided differences with h = 1): \n" << ddDelta(b1, 1.0) << endl;	// get call delta
	b1.setType("P");	// set to put option
	p2 = b1.Price();	// get exact put price
	cout << "Put price: \n" << p2 << endl;
	cout << b1.ParityPrice(p2) << endl;	// find call price using put price and put-call parity
	cout << "Put delta: \n" << b1.Delta() << endl;	// get put delta
	cout << "Gamma: \n" << b1.Gamma() << endl;	// get gamma
	b1.Parity(p1, p2);	// check if put-call parity holds
	cout << "Put delta (divided differences with h = 1): \n" << ddDelta(b1, 1.0) << endl;	// get put delta
	cout << "Gamma (divided differences with h = 1): \n" << ddGamma(b1, 1.0) << endl;	// get gamma

	// ============ Matrix input ============

	map<string, vector<double>> matrix1;	// create an input matrix in form of a map
	matrix1["T"] = Mesh(0.5, 3.5, 0.5);
	matrix1["K"] = Mesh(100.0);
	matrix1["sig"] = Mesh(0.36, 0.6, 0.04);
	matrix1["r"] = Mesh(0.1);
	matrix1["S"] = Mesh(105.0);
	matrix1["b"] = Mesh(0.0);
	EuropeanMatrix optMat1;
	optMat1.setParam(matrix1);	// takes a matrix of parameters as input

	optMat1.setType("C");
	optMat1.updateMatrix();
	cout << "\nCall delta (matrix input): " << endl;
	printMesh(optMat1.getDelta());
	cout << "\nCall delta (divided differences with h = 1): " << endl;
	printMesh(optMat1.getddDelta(1));

	optMat1.setType("P");
	optMat1.updateMatrix();
	cout << "\nPut Delta (matrix input): " << endl;
	printMesh(optMat1.getDelta());
	cout << "\nPut delta (divided differences with h = 1): " << endl;
	printMesh(optMat1.getddDelta(1));

	cout << "\nGamma (matrix input): " << endl;
	printMesh(optMat1.getGamma());
	cout << "\nGamma (divided differences with h = 1): " << endl;
	printMesh(optMat1.getddGamma(1));

	return 0;
}
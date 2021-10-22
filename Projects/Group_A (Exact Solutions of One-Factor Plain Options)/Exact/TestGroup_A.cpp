// File name: TestGroup_A.cpp
// Author: Li Jin Chen
// Exercise: 9.Group_A
// Description: This is a file for testing the functionalities of EuropeanOption and EuropeanMatrix classes. 
//		EuropeanOption is used for a single option, while EuropeanMatrix can take a matrix (in form of a map) 
//		as input and give a price vector as output. This file also tests the calculation of delta and gamma, 
//		both through exact formulas and through divided differences. 


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
	// ============== A.1.a & A.1.b ==============

	double p1;
	double p2;

	// tests Batch 1
	EuropeanOption b1;
	b1.setParam("T", 0.25);	// enter the paramters
	b1.setParam("K", 65);
	b1.setParam("sig", 0.30);
	b1.setParam("r", 0.08);
	b1.setParam("S", 60);
	b1.setParam("b", b1.getParam("r"));	// b = r
	b1.setType("C");	// set to call option
	
	cout << "Batch 1" << endl;
	p1 = b1.Price();	// get exact call price
	cout << "Call price: \n" << p1 << endl;
	cout << b1.ParityPrice(p1) << endl;	// find put price using call price and put-call parity
	b1.setType("P");	// set to put option
	p2 = b1.Price();	// get exact put price
	cout << "Put price: \n" << p2 << endl;
	cout << b1.ParityPrice(p2) << endl;	// find call price using put price and put-call parity
	b1.Parity(p1, p2);	// check if put-call parity holds

	// tests Batch 2, calling same functions as Batch 1
	EuropeanOption b2;
	b2.setParam("T", 1.0);
	b2.setParam("K", 100);
	b2.setParam("sig", 0.2);
	b2.setParam("r", 0.0);
	b2.setParam("S", 100);
	b2.setParam("b", b2.getParam("r"));
	b2.setType("C");
	
	cout << "\nBatch 2" << endl;
	p1 = b2.Price();
	cout << "Call price: \n" << p1 << endl;
	cout << b2.ParityPrice(p1) << endl;
	b2.setType("P");
	p2 = b2.Price();
	cout << "Put price: \n" << p2 << endl;
	cout << b2.ParityPrice(p2) << endl;
	b2.Parity(p1, p2);

	// tests Batch 3, calling same functions as Batch 1
	EuropeanOption b3;
	b3.setParam("T", 1.0);
	b3.setParam("K", 10);
	b3.setParam("sig", 0.50);
	b3.setParam("r", 0.12);
	b3.setParam("S", 5);
	b3.setParam("b", b3.getParam("r"));
	b3.setType("C");
	
	cout << "\nBatch 3" << endl;
	p1 = b3.Price();
	cout << "Call price: \n" << p1 << endl;
	cout << b3.ParityPrice(p1) << endl;
	b3.setType("P");
	p2 = b3.Price();
	cout << "Put price: \n" << p2 << endl;
	cout << b3.ParityPrice(p2) << endl;
	b3.Parity(p1, p2);

	// tests Batch 4, calling same functions as Batch 1
	EuropeanOption b4;
	b4.setParam("T", 30.0);
	b4.setParam("K", 100.0);
	b4.setParam("sig", 0.30);
	b4.setParam("r", 0.08);
	b4.setParam("S", 100.0);
	b4.setParam("b", b4.getParam("r"));
	b4.setType("C");
	
	cout << "\nBatch 4" << endl;
	p1 = b4.Price();
	cout << "Call price: \n" << p1 << endl;
	cout << b4.ParityPrice(p1) << endl;
	b4.setType("P");
	p2 = b4.Price();
	cout << "Put price: \n" << p2 << endl;
	cout << b4.ParityPrice(p2) << endl;
	b4.Parity(p1, p2);

	// ============== A.1.c ==============

	EuropeanMatrix optMat1;	// EuropeanMatrix can take vectors as input and give a vector as output
	optMat1.setParam("T", 0.25);	// enter the parameters
	optMat1.setParam("K", 30);
	optMat1.setParam("sig", 0.30);
	optMat1.setParam("r", 0.08);
	optMat1.setParam("S", 10.0, 50.0, 1.0);	// let underlying price vary from 10 to 50 by increment of 1
	optMat1.setParam("b", optMat1.getParam("r"));	// b = r
	optMat1.setType("C");	// set to call option
	
	optMat1.updateMatrix();	// set all input vectors to same size
	cout << "\nVarying underlying price: " << endl;
	printMesh(optMat1.getPrice());	// price vector as output

	// ============== A.1.d ==============

	// same as A.1.c, but letting expiry time to vary
	optMat1.setParam("T", 0.25, 3.25, 0.5);	// let expiry time vary from 0.25 to 3.25 by increment of 0.5
	optMat1.setParam("K", 65);
	optMat1.setParam("sig", 0.30);
	optMat1.setParam("r", 0.08);
	optMat1.setParam("S", 60);
	optMat1.setParam("b", optMat1.getParam("r"));
	optMat1.setType("C");
	
	optMat1.updateMatrix();
	cout << "\nVarying expiry time: " << endl;
	printMesh(optMat1.getPrice());

	// same as A.1.c, but letting volatility to vary
	optMat1.setParam("T", 0.25);
	optMat1.setParam("K", 65);
	optMat1.setParam("sig", 0.30, 0.60, 0.05);	// let volatility vary from 0.3 to 0.6 by increment of 0.05
	optMat1.setParam("r", 0.08);
	optMat1.setParam("S", 60);
	optMat1.setParam("b", optMat1.getParam("r"));
	optMat1.setType("C");
	
	optMat1.updateMatrix();
	cout << "\nVarying volatility: " << endl;
	printMesh(optMat1.getPrice());

	// takes a matrix of parameters as input
	map<string, vector<double>> matrix1;	// create an input matrix in form of a map
	matrix1["T"] = Mesh(0.25);
	matrix1["K"] = Mesh(45.0, 80.0, 5.0);	// let strike price vary
	matrix1["sig"] = Mesh(0.30);
	matrix1["r"] = Mesh(0.03, 0.10, 0.01);	// let risk-free rate vary
	matrix1["S"] = Mesh(60.0);
	matrix1["b"] = Mesh(0.0);
	optMat1.setParam(matrix1);	// takes a matrix of parameters as input
	optMat1.setType("C");
	
	optMat1.updateMatrix();
	cout << "\nVarying strike price and risk-free rate: " << endl;
	printMesh(optMat1.getPrice());

	// ============== A.2.a ==============

	// tests the given batch
	EuropeanOption b5;
	b5.setParam("K", 100);
	b5.setParam("S", 105);
	b5.setParam("T", 0.5);
	b5.setParam("r", 0.1);
	b5.setParam("b", 0);
	b5.setParam("sig", 0.36);
	b5.setType("C");
	
	cout << "\nDelta" << endl;
	cout << "Call delta: \n" << b5.Delta() << endl;	// get call delta
	b5.setType("P");
	cout << "Put delta: \n" << b5.Delta() << endl;	// get put delta
	cout << "Gamma: \n" << b5.Gamma() << endl;	// get gamma

	// ============== A.2.b ==============

	EuropeanMatrix optMat2;
	optMat2.setParam("T", 0.5);
	optMat2.setParam("K", 30);
	optMat2.setParam("sig", 0.36);
	optMat2.setParam("r", 0.1);
	optMat2.setParam("S", 10, 50, 1);	// let underlying price vary from 10 to 50 by increment of 1
	optMat2.setParam("b", 0);
	
	optMat2.setType("C");
	optMat2.updateMatrix();
	cout << "\nCall Delta (varying underlying price): " << endl;
	printMesh(optMat2.getDelta());	// a vector of call delta as output
	
	optMat2.setType("P");
	optMat2.updateMatrix();
	cout << "\nPut Delta (varying underlying price): " << endl;
	printMesh(optMat2.getDelta());	// a vector of put delta as output
	
	cout << "\nGamma (varying underlying price): " << endl;
	printMesh(optMat2.getGamma());	// a vector of gamma as output

	// ============== A.2.c ==============

	map<string, vector<double>> matrix2;	// create an input matrix in form of a map
	matrix2["T"] = Mesh(0.5, 3.5, 0.5);	// let expiry time vary
	matrix2["K"] = Mesh(100.0);
	matrix2["sig"] = Mesh(0.36, 0.6, 0.04);	// let volatility vary
	matrix2["r"] = Mesh(0.1);
	matrix2["S"] = Mesh(105.0);
	matrix2["b"] = Mesh(0.0);
	EuropeanMatrix optMat3;
	optMat3.setParam(matrix2);	// takes a matrix of parameters as input
	
	optMat3.setType("C");
	optMat3.updateMatrix();
	cout << "\nCall Delta (varying expiry time and volatility): " << endl;
	printMesh(optMat3.getDelta());	// a vector of call delta as output
	
	optMat3.setType("P");
	optMat3.updateMatrix();
	cout << "\nPut Delta (varying expiry time and volatility): " << endl;
	printMesh(optMat3.getDelta());	// a vector of put delta as output
	
	cout << "\nGamma (varying expiry time and volatility): " << endl;
	printMesh(optMat3.getGamma());	// a vector of gamma as output

	// ============== A.2.d ==============
	
	// redoing A.2.a with divided differences
	b5.setType("C");
	cout << "\nCall delta (divided differences with h = 1): \n" << ddDelta(b5, 1.0) << endl;	// get call delta
	cout << "Call delta (divided differences with h = 0.5): \n" << ddDelta(b5, 0.5) << endl;
	cout << "Call delta (divided differences with h = 0.1): \n" << ddDelta(b5, 0.1) << endl;
	b5.setType("P");
	cout << "Put delta (divided differences with h = 1): \n" << ddDelta(b5, 1.0) << endl;	// get put delta
	cout << "Put delta (divided differences with h = 0.5): \n" << ddDelta(b5, 0.5) << endl;
	cout << "Put delta (divided differences with h = 0.1): \n" << ddDelta(b5, 0.1) << endl;
	cout << "Gamma (divided differences with h = 1): \n" << ddGamma(b5, 1.0) << endl;	// get gamma
	cout << "Gamma (divided differences with h = 0.5): \n" << ddGamma(b5, 0.5) << endl;
	cout << "Gamma (divided differences with h = 0.1): \n" << ddGamma(b5, 0.1) << endl;

	// redoing A.2.b with divided differences (S varies from 10 to 50 by increment of 1)
	optMat2.setType("C");
	optMat2.updateMatrix();
	cout << "\nCall delta (divided differences with h = 1): " << endl;
	printMesh(optMat2.getddDelta(1));	// a vector of approximated put delta as output
	cout << "\nCall delta (divided differences with h = 0.5): " << endl;
	printMesh(optMat2.getddDelta(0.5));
	cout << "\nCall delta (divided differences with h = 0.1): " << endl;
	printMesh(optMat2.getddDelta(0.1));

	optMat2.setType("P");
	optMat2.updateMatrix();
	cout << "\nPut delta (divided differences with h = 1): " << endl;
	printMesh(optMat2.getddDelta(1));	// a vector of approximated put delta as output
	cout << "\nPut delta (divided differences with h = 0.5): " << endl;
	printMesh(optMat2.getddDelta(0.5));
	cout << "\nPut delta (divided differences with h = 0.1): " << endl;
	printMesh(optMat2.getddDelta(0.1));
	
	cout << "\nGamma (divided differences with h = 1): " << endl;
	printMesh(optMat2.getddGamma(1));	// a vector of approximated gamma as output
	cout << "\nGamma (divided differences with h = 0.5): " << endl;
	printMesh(optMat2.getddGamma(0.5));
	cout << "\nGamma (divided differences with h = 0.1): " << endl;
	printMesh(optMat2.getddGamma(0.1));
	cout << "\nGamma (divided differences with h = 0.01): " << endl;
	printMesh(optMat2.getddGamma(0.01));

	return 0;
}
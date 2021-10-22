// File name: TestGroup_B.cpp
// Author: Li Jin Chen
// Exercise: 9.Group_B
// Description: This is a file for testing the functionalities of PAmericanOption and PAmericanMatrix classes. 
//		PAmericanOption is used for a single perpetual American option, while PAmericanMatrix can take a matrix 
//		(in form of a map) as input and give a price vector as output. Exact formulas are used for calculating
//		call and put prices. 


#include "Mesher.hpp"
#include "PAmericanOption.hpp"
#include "PAmericanMatrix.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
	// ============== B.a & B.b ==============

	double p1;
	double p2;

	// test batch
	PAmericanOption b1;
	b1.setParam("K", 100);	// enter the paramters
	b1.setParam("sig", 0.1);
	b1.setParam("r", 0.1);
	b1.setParam("S", 110);
	b1.setParam("b", 0.02);
	
	cout << "Test Batch" << endl;
	b1.setType("C");	// set to call option
	p1 = b1.Price();	// get exact call price
	cout << "Call price: \n" << p1 << endl;
	b1.setType("P");	// set to put option
	p2 = b1.Price();	// get exact put price
	cout << "Put price: \n" << p2 << endl;

	// ============== B.c ==============

	PAmericanMatrix optMat1;	// PAmericanMatrix can take vectors as input and give a vector as output
	optMat1.setParam("K", 30);
	optMat1.setParam("sig", 0.30);
	optMat1.setParam("r", 0.08);
	optMat1.setParam("S", 10, 50, 10);
	optMat1.setParam("b", 0.04);
	optMat1.setType("C");

	optMat1.updateMatrix();	// set all input vectors to same size
	cout << "\nVarying one parameter: " << endl;
	printMesh(optMat1.getPrice());	// price vector as output

	// ============== B.d ==============

	map<string, vector<double>> matrix1;	// create an input matrix in form of a map
	matrix1["K"] = Mesh(85.0, 115.0, 5.0);
	matrix1["sig"] = Mesh(0.36, 0.6, 0.04);
	matrix1["r"] = Mesh(0.1);
	matrix1["S"] = Mesh(105.0);
	matrix1["b"] = Mesh(0.0);
	optMat1.setParam(matrix1);	// takes a matrix of parameters as input
	optMat1.setType("C");

	optMat1.updateMatrix();
	cout << "\nCall price (matrix input): " << endl;
	printMesh(optMat1.getPrice());
	optMat1.setType("P");
	optMat1.updateMatrix();
	cout << "\nPut price (matrix input): " << endl;
	printMesh(optMat1.getPrice());

	return 0;
}
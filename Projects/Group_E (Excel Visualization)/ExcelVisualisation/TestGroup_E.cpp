// File name: TestGroup_E.cpp
// Author: Li Jin Chen
// Exercise: 9.Group_E
// Description: This is a file for testing C++ code that can visualize data on Excel. It creates a single 
//		curve of option price vs underlying stock price. 


#include "Mesher.hpp"
#include "EuropeanOption.hpp"
#include "EuropeanMatrix.hpp"
#include "ExcelDriverLite.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
	EuropeanMatrix optMat1;	// EuropeanMatrix can take vectors as input and give a vector as output
	optMat1.setParam("T", 0.25);
	optMat1.setParam("K", 30);
	optMat1.setParam("sig", 0.30);
	optMat1.setParam("r", 0.08);
	optMat1.setParam("S", 10.0, 50.0, 1.0);	// let underlying price vary from 10 to 50 by increment of 1
	optMat1.setParam("b", optMat1.getParam("r"));	// b = r
	optMat1.setType("C");	// set to call option

	optMat1.updateMatrix();	// set all input vectors to same size
	cout << "Varying underlying price: " << endl;
	vector<double> priceVec = optMat1.getPrice();
	printMesh(priceVec);	// print results to console

	ExcelDriver xl; xl.MakeVisible(true);	// open Excel
	// print data to Excel and create chart
	xl.CreateChart(optMat1.getParam("S"), priceVec, "Option Price", "Price of Underlying", "");

	return 0;
}
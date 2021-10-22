// File name: Mesher.hpp
// Author: Li Jin Chen
// Exercise: 9.Group_A
// Description: Mesh is a utility function for creating vector instances. Here also includes printMesh(), which 
//		helps print out a vector. 


#ifndef Mesher_HPP
#define Mesher_HPP

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

// creates a mesh array of doubles separated by a mesh size h
inline vector<double> Mesh(double a, double b, double h)
{
	if (h == 0.0)	// prevents mesh of infinite length
	{
		return vector<double>(1, a);
	}

	if (h * (b - a) < 0.0)	// makes sure start point and end point makes sense
	{
		double tmp = a;
		a = b;
		b = tmp;
	}

	vector<double> result;	// holds the result
	for (double j = a; j < b + h / 1000.0; j += h)
	{// h / 1000.0 allows for a small tolerance, otherwise end point is not always included when should be
		result.push_back(j);
	}

	return result;
}

// creates a single member vector
template <typename T>
inline vector<T> Mesh(const T& a)
{
	return vector<T>(1, a);
}

// prints out a vector, useful when testing
template <typename T>
inline void printMesh(const vector<T>& mesh0)
{
	for (unsigned int j = 0; j < mesh0.size(); j++)
	{
		cout << mesh0[j] << endl;
	}
}

#endif
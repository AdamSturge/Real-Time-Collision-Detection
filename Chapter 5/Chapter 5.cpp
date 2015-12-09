// Chapter 5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "closestpointcomputations.h"
#include <armadillo>

using namespace arma;
using namespace std;

int main()
{	
	vec3 a = vec3("0.0 0.0 0.0");
	vec3 b = vec3("1.0 0.0 0.0");
	vec3 c = vec3("0.5 0.5 0.0");
	vec3 p = vec3("3.21 4.23 6.77");

	vec3 q = ClosestPointToTriangle(p, a, b, c);

	for each(float i in q) {
		cout << i << endl;
	}

	system("pause");

}


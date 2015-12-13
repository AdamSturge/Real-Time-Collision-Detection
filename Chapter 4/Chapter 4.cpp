// Chapter 4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "bounding_volumes.h"
#include <armadillo>

using namespace arma;


int main()
{
	Sphere s;
	s.c = vec3("0.0 0.0 0.0");
	s.r = 1.0f;

	vec3 pt[] = { vec("0.0 0.5 0.0"),vec("0.0 1.0 0.0"),vec("1.0 0.0 0.0"),vec("2.0 0.8 0.3"),vec("1.5 0.22 1.23"),vec("4.0 0.0 1.68") };
	int numPts = 6;

	RitterSphere(s, pt, numPts);

	cout << s.c[0] << " " << s.c[1] << " " << s.c[2] << endl;
	cout << s.r << endl;
	
	system("pause");
}


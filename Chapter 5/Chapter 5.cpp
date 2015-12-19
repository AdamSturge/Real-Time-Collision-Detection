// Chapter 5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "closest_point_computations.h"
#include "dynamic_intersection_tests.h"
#include "seperating_axis.h"
#include <armadillo> 

using namespace arma;
using namespace std;


int main()
{	
	vector<vec2> V0 = vector<vec2>(3);

	vec2 p0 = vec2("3.5 0.0");
	vec2 p1 = vec2("5.0 0.0");
	vec2 p2 = vec2("4.5 1.0");

	V0[0] = p0;
	V0[1] = p1;
	V0[2] = p2;

	ConvexPolygon c0 = ConvexPolygon(V0);

	vector<vec2> V1 = vector<vec2>(3);

	vec2 p3 = vec2("6.0 0.0");
	vec2 p4 = vec2("7.0 0.0");
	vec2 p5 = vec2("3.5 1.0");

	V1[0] = p3;
	V1[1] = p4;
	V1[2] = p5;

	ConvexPolygon c1 = ConvexPolygon(V1);

	if (TestIntersection(c0, c1)) {
		cout << "they intersect" << endl;
	}
	else {
		cout << "they don't intersect" << endl;
	}

	system("pause");

}


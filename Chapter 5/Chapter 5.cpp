// Chapter 5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "closest_point_computations.h"
#include "dynamic_intersection_tests.h"
#include <armadillo>

using namespace arma;
using namespace std;
using namespace dynam_interaction_test;

int main()
{	
	/*
	vec3 a = vec3("0.0 0.0 0.0");
	vec3 b = vec3("1.0 0.0 0.0");
	vec3 c = vec3("0.5 0.5 0.0");
	vec3 p = vec3("3.21 4.23 6.77");

	vec3 q = ClosestPointToTriangle(p, a, b, c);

	for each(float i in q) {
		cout << i << endl;
	}
	*/

	Sphere s0;
	s0.c = vec3("0.0 0.0 0.0");
	s0.r = 1.0f;

	Sphere s1;
	s1.c = vec3("2.6 0.0 0.0");
	s1.r = 1.0f;

	vec3 d = vec3("1.0 0.0 0.0");

	float t = -1.0f;
	if (TestMovingSphereSphere(s0, d, 0.0f, 1.0f, s1, t)) {
		cout << "Sphere s0 intersects s1 at time t=" << t << endl;
	}
	else {
		cout << "Sphere s0 does not intersect s1" << endl;
	}

	system("pause");

}


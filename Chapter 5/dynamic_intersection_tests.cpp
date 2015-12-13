
#include "stdafx.h"
#include "dynamic_intersection_tests.h"
#include <armadillo>

using namespace arma;

namespace dynam_interaction_test {
	const double INTERVAL_EPSILON = 0.000001;

	int TestSphereSphere(Sphere s0, Sphere s1)
	{
		vec3 d = s0.c - s1.c;
		float dist2 = dot(d, d);
		
		float radiusSum = s0.r + s1.r;
		
		return dist2 <= radiusSum*radiusSum;
	}

	int TestMovingSphereSphere(Sphere s0, arma::vec3 d, float t0, float t1, Sphere s1, float& t)
	{
		// Compute sphere bounding motion of s0 during time inercal from t0 to t1
		Sphere b;
		float mid = (t0 + t1) / 2;
		b.c = s0.c + mid*d;
		b.r = s0.r + (mid - t0)*norm(d);

		// If bounding sphere not overlapping s1, then no collision in this interval
		if (!TestSphereSphere(b, s1)) return 0;

		// Cannot rule out collision : recurse for more accurate testing. 
		// To terminiate the recursion, collision is assumed when tume interval becomes sufficently small
		if (t1 - t0 < INTERVAL_EPSILON) {
			t = t0;
			return 1;
		}

		// Recursively test first half of interval. Return collsion if detected
		if (TestMovingSphereSphere(s0, d, t0, mid, s1, t)) return 1;

		// Recursively test second half of interval
		return TestMovingSphereSphere(s0, d, mid, t1, s1, t);


	}

}

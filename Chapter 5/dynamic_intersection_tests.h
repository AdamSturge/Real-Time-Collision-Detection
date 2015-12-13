#pragma once

#include "stdafx.h"
#include <armadillo>

namespace dynam_interaction_test {
	struct Sphere {
		arma::vec3 c;
		float r;
	};

	// Static sphere intersection test
	int TestSphereSphere(Sphere s0, Sphere s1);

	// Tests if sphere s0 moving along direction d from t0 to t1 intersects static sphere s1.
	// If collision is found, updates t with time of collision
	int TestMovingSphereSphere(Sphere s0, arma::vec3 d, float t0, float t1, Sphere s1, float &t);
}




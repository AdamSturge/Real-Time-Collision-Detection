#pragma once

#include <armadillo>

struct Plane {
	arma::vec3 n;
	float d;
};

float DistPointPlane(arma::vec3 q, Plane p);

arma::vec3 ClosestPointToPlane(arma::vec3 q, Plane p);

arma::vec3 ClosestPointToTriangle(arma::vec3 p, arma::vec3 a, arma::vec3 b, arma::vec3 c);



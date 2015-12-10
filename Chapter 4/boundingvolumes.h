#pragma once

#include <armadillo>

struct Sphere {
	arma::vec3 c;
	float r;
};

void MostSeperatedPointsOnAABB(int &min, int &max, arma::vec3 pt[], int numPts);

void SphereFromDistantPoints(Sphere &s, arma::vec3 pt[], int numPts);

void SphereOfSphereAndPt(Sphere &s, arma::vec3 &p);

void RitterSphere(Sphere &s, arma::vec3 pt[], int numPts);

#include "stdafx.h"
#include <armadillo>
#include "bounding_volumes.h"


using namespace arma;

// Finds most seperated points on an axis aligned bounding box containing the points
void MostSeperatedPointsOnAABB(int &min, int &max, arma::vec3 pt[], int numPts)
{
	// First find most extreme points along principal axes
	int minx = 0, maxx = 0, miny = 0, maxy = 0, minz = 0, maxz = 0;
	for (int i = 1; i < numPts; ++i) {
		if (pt[i][0] < pt[minx][0]) minx = i;
		if (pt[i][0] > pt[maxx][0]) maxx = i;
		if (pt[i][1] < pt[miny][1]) miny = i;
		if (pt[i][1] > pt[maxy][1]) maxy = i;
		if (pt[i][2] < pt[minz][2]) minz = i;
		if (pt[i][2] > pt[maxz][2]) maxz = i;
	}

	// Compute the squared distances for the three pairs of points
	float dist2x = dot(pt[maxx] - pt[minx], pt[maxx] - pt[minx]);
	float dist2y = dot(pt[maxy] - pt[miny], pt[maxy] - pt[miny]);
	float dist2z = dot(pt[maxz] - pt[minz], pt[maxz] - pt[minz]);

	// Pick pair of (min,max) of points most distant
	min = minx;
	max = maxx;
	if (dist2y > dist2x && dist2y > dist2z) {
		min = miny;
		max = maxy;
	}
	if (dist2z > dist2x && dist2z > dist2y) {
		min = minz;
		max = maxz;
	}

}

// Computes a sphere that is centered mid way between the exteme points
// whose radius is half the distance between them
void SphereFromDistantPoints(Sphere &s, arma::vec3 pt[], int numPts)
{
	// Find the most separated point pair defining the encompassing AABB
	int min, max;
	MostSeperatedPointsOnAABB(min, max, pt, numPts);

	// Set up sphere tp just encompass these two points
	s.c = (pt[min] + pt[max]) * 0.5f;
	s.r = dot(pt[max] - s.c, pt[max] - s.c);
	s.r = sqrt(s.r);
}

// Given a sphere and a point moves and grows the sphere to include the point 
// while maintaining all other points in the sphere
void SphereOfSphereAndPt(Sphere &s, vec3 &p) {
	// Compute distance squared between point and center of sphere
	vec3 d = p - s.c;
	float dist2 = dot(d, d);

	// Only update s if point p is outside it
	if (dist2 > s.r*s.r) {
		float dist = sqrt(dist2);
		float newRadius = (s.r + dist) * 0.5f;
		d = d / dist; // normalize direction vector
		s.r = newRadius;
		s.c += (newRadius - s.r)*d; // Move center along d
	}
}

// Compute Ritter sphere for a set of points 
// https://en.wikipedia.org/wiki/Bounding_sphere#Ritter.27s_bounding_sphere
void RitterSphere(Sphere &s, arma::vec3 pt[], int numPts)
{
	// Get sphere encompassing two approximately most distant points
	SphereFromDistantPoints(s, pt, numPts);

	// Grow sphere to include all points
	for (int i = 0; i < numPts; ++i) {
		SphereOfSphereAndPt(s, pt[i]);
	}
}

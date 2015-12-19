#include "stdafx.h"
#include "seperating_axis.h"
#include <armadillo>

using namespace std;
using namespace arma;

ConvexPolygon::ConvexPolygon(vector<vec2> V)
{
	this->V = V;
	
	int n = V.size();
	this->E = vector<vec2>(n);
	for (int i = 0; i < n; ++i) {
		this->E[i] = V[(i + 1) % n] - V[i % n];
	}

	N = vector<vec2>(n);
	vec2 normal;
	for (int i = 0; i < n; ++i) {
		normal = vec2();
		normal[0] = E[i][1];
		normal[1] = -1*E[i][0];
		normal = normal / norm(normal);
		N[i] = normal;
	}
}

int ConvexPolygon::GetN()
{
	return V.size();
}

vec2 ConvexPolygon::GetVertex(int i)
{
	int n = GetN();
	return V[i % n];
}

vec2 ConvexPolygon::GetEdge(int i)
{
	int n = GetN();
	return E[i % n];
}

vec2 ConvexPolygon::GetNormal(int i)
{
	int n = GetN();
	return N[i % n];
}

int WhichSide(ConvexPolygon c, vec2 p, vec2 d)
{
	// C vertices are projected onto line P+tD. 
	// Return value is +1 if all t>0, -1 if all t<0, 
	// or 0 if the line splits the polygon

	int posCount = 0;
	int negCount = 0;
	int zeroCount = 0;
	double t = 0.0f;
	for (int i = 0; i < c.GetN(); ++i) {
		t = dot(d, c.GetVertex(i) - p);
		if (t > 0) {
			posCount++;
		}
		else if (t < 0) {
			negCount++;
		}
		else {
			zeroCount++;
		}

		if ((posCount > 0 && negCount > 0) || zeroCount > 0) {
			return 0;
		}
	}

	return posCount ? 1 : -1;
}

bool TestIntersection(ConvexPolygon c0, ConvexPolygon c1)
{
	// Test edges of C0 for separation. Because of the counterclockwise
	// ordering, the projection interval for C0 is [m,0] where m <= 0.
	// Only try to determine if C1 is on the 'positive' side of the line	
	for (int i = 0; i < c0.GetN(); i++) {
		vec2 p = c0.GetVertex(i);
		vec2 d = c0.GetNormal(i);
		if (WhichSide(c1, p, d) > 0) {

			// C1 is entirely on 'positive' side of line P+tD
			return false;
		}
	}

	// Test edges of C1 for separation. Because of the counterclockwise
	// ordering, the projection interval for C1 is [m,0] where m <= 0.
	// Only try to determine if C0 is on the 'positive' side of the line	
	for (int i = 0; i < c1.GetN(); i++) {
		vec2 p = c1.GetVertex(i);
		vec2 d = c1.GetNormal(i);
		if (WhichSide(c0, p, d) > 0) {

			// C0 is entirely on 'positive' side of line P+tD
			return false;
		}
	}

	return true;
}



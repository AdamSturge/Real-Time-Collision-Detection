#include "stdafx.h"
#include <armadillo>
#include "closestpointcomputations.h"

using namespace arma;

float DistPointPlane(vec3 q, Plane p)
{
	return (dot(p.n, q) - p.d) / dot(p.n, p.n);
}

vec3 ClosestPointToPlane(vec3 q, Plane p)
{
	float t = DistPointPlane(q, p);
	return q - t*p.n;
}

// TO DO: Use Lagrande identity to replace cross() with dot() 
// https://en.wikipedia.org/wiki/Cross_product#Lagrange.27s_identity
vec3 ClosestPointToTriangle(vec3 p, arma::vec3 a, vec3 b, vec3 c)
{
	// Compute parametric position s for project P' of P on AB
	// P' = A + sAB, s = snom/(snom + sdenom)
	float snom = dot(p - a, b - a), sdenom = dot(p - b, a - b);
	
	// Compute parametric position t for project P' of P on AC
	// P' = A + tAC, t = tnom/(tnom + tdenom)
	float tnom = dot(p - a, c - a), tdenom = dot(p - c, a - c);

	if (snom <= 0.0f && tnom <= 0.0f)	return a; // Vertex region early out

	// Compute parametric position u for project P' of P on BC
	// P' = B + uBC, u = unom/(unom + udenom)
	float unom = dot(p - b, c - b), udenom = dot(p - c, b - c);

	if (sdenom <= 0.0f && unom <= 0.0f)	return b; // Vertex region early out
	if (tdenom <= 0.0f && udenom <= 0.0f)	return c; // Vertex region early out

	// P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
	vec3 n = cross(b - a, c - a);
	float vc = dot(n, cross(a - p, b - p));
	// If P outside AB and within feature region of AB return projection of P onto AB
	if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
		return a + snom / (snom + sdenom) * (b - a);

	// P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
	float va = dot(n, cross(b - p, c - p));
	// If P outside BC and within feature region of BC return projection of P onto BC
	if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
		return b + unom / (unom + udenom) * (c - b);

	// P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
	float vb = dot(n, cross(c - p, a - p));
	// If P outside BC and within feature region of BC return projection of P onto BC
	if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
		return a + tnom / (tnom + tdenom) * (c - a);

	// P must project inside face region, Compute Q using barycentric coordinates
	float u = va / (va + vb + vc);
	float v = vb / (va + vb + vc);
	float w = 1.0f - u - v;
	return u*a + v*b + w*c;
}


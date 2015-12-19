#pragma once
#include "stdafx.h"
#include <armadillo>

class ConvexPolygon {
	private:
		std::vector<arma::vec2> V; // Vertex list (coutnerclockwise)
		std::vector<arma::vec2> E; // Edge list (coutnerclockwise)
		std::vector<arma::vec2> N; // Normal list (coutnerclockwise, outward pointing)

	public :
		ConvexPolygon(std::vector<arma::vec2> V);
		int GetN();
		arma::vec2 GetVertex(int i);
		arma::vec2 GetEdge(int i);
		arma::vec2 GetNormal(int i);
};

int WhichSide(ConvexPolygon c, arma::vec2 p, arma::vec2 d);

bool TestIntersection(ConvexPolygon c0, ConvexPolygon c1);
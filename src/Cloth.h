#pragma once
#include "Cloth.h"
#include "Particles.h"
#include "Particle.h"
#include "DistanceConstraint.h"
#include "BendingConstraint.h"

class Cloth {
public:
	Cloth(int nCols, int nRow, int nSize);
	void draw();
	void update();
	
	Particles particles;
	Particle& getAt(int nCol, int nRow);
	
	int const rows;
	int const cols;
	int const size;
	int const width;
	int const height;
};
#include "Cloth.h"

Cloth::Cloth(int nCols, int nRows, int nSize)
:cols(nCols)
,rows(nRows)
,size(nSize)
,width(cols * nSize)
,height(rows * nSize)
{
	// create particles.
	for(int j = 0; j < rows; ++j) {
		for(int i = 0 ; i < cols; ++i) {
			ofVec3f pos(i * size, 0 ,j * size);
			Particle* part = new Particle(pos,1.0f);
			//if(j == 0 || j == (rows-1) || i == 0 || i == (cols-1)) {
			if(j == 0 || j == 1) {
				part->disabled = true;
				part->inv_mass = .0f;
			}
			particles.addParticle(part);
		}	
	}
	
	// create distance constraints.
	for(int i = 0; i < cols; ++i) {
		for(int j = 0; j < rows; ++j) {
			if(i < cols-1) {
				DistanceConstraint* con = new DistanceConstraint(&getAt(i,j), &getAt(i+1,j));
				particles.addConstraint(con);
			}
			if(j < rows-1) {
				DistanceConstraint* con = new DistanceConstraint(&getAt(i,j), &getAt(i,j+1));
				particles.addConstraint(con);
			}
		}
	}
	
	// create bending constraints
	for(int i = 0; i < cols; ++i) {
		for(int j = 0; j < rows-2; ++j) {
			BendingConstraint* con = new BendingConstraint(&getAt(i,j), &getAt(i, j+1), &getAt(i, j+2));
			particles.addConstraint(con);
		}
	}
}

void Cloth::update() {
	particles.update(0.08);
}

void Cloth::draw() {
	particles.draw();
}

Particle& Cloth::getAt(int nCol, int nRow) {
	int dx = (nRow * cols) + nCol;
	return *particles.particles.at(dx);
}
#include "Cloth.h"

Cloth::Cloth(int nCols, int nRows, int nSize)
:cols(nCols)
,rows(nRows)
,size(nSize)
{
	// create particles.
	for(int j = 0; j < rows; ++j) {
		for(int i = 0 ; i < cols; ++i) {
			ofVec3f pos(40+i * size, 40+j * size, 0);
			Particle* part = new Particle(pos,1);
			if(j == 0 || j == (rows-1) || i == 0 || i == (cols-1)) {
				part->disabled = true;
				part->inv_mass = .0f;
			}
			
			particles.addParticle(part);
			
		}	
	}
	
	// create constraints.
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
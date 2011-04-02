#include "Particle.h"
Particle::Particle(ofVec3f oPosition, float nMass)
:position(oPosition)
,mass(nMass)
,velocity(0,0,0)
,displacement(0,0,0)
{
	if(mass <= 0.0) {	
		mass = 0.001;
		inverse_mass = 0;
	}
	else {
		inverse_mass = 1/mass;
	}
	
}

void Particle::addDisplacement(ofVec3f oDisplacement) {
	displacement += (oDisplacement * inverse_mass);
}

void Particle::update() {
	
}

void Particle::draw() {
	glColor3f(1,0,0);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex3fv(position.getPtr());
	glEnd();
	glColor3f(1,1,1);
	glPointSize(1);
}
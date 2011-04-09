#include "Particle.h"
Particle::Particle(ofVec3f oPosition, float nMass)
:pos(oPosition)
,tmp_pos(0,0,0)
,mass(nMass)
,vel(0,0,0)
,disabled(false)
{
	if(mass <= 0.0) {	
		mass = 0.001;
		inv_mass = 0;
		disabled = true;
	}
	else {
		inv_mass = 1/mass;
	}
}

void Particle::addForce(ofVec3f oForce) {
	vel += (oForce*inv_mass);
}

void Particle::update() {
	
}

void Particle::draw() {
	if(disabled) {
		glColor3f(1,0,0);
	}
	else {
		glColor3f(0,1,0);
	}
	
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex3fv(pos.getPtr());
	glEnd();
	glColor3f(1,1,1);
	glPointSize(1);
}
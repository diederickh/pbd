#include "DistanceConstraint.h"
#include "Particle.h"

DistanceConstraint::DistanceConstraint(Particle* pA, Particle* pB) 
:a(pA)
,b(pB)
,Constraint()
{
	rest_length = (b->position - a->position).length();
	k = 0.007;
}


// lines 9-11
void DistanceConstraint::update() {
	ofVec3f dir = b->predicted_position - a->predicted_position;
	
	float d = dir.length();
	float f = (rest_length - d) * k;
	dir.normalize();
	dir *= f;
	
	// okay now apply the force
	a->addDisplacement(-dir);
	b->addDisplacement(dir);
}

void DistanceConstraint::draw() {
	glColor4f(0.3, 0.3, 0.3, 0.6f);
	glBegin(GL_LINES);
		glVertex3fv(a->position.getPtr());
		glVertex3fv(b->position.getPtr());
	glEnd();
	glColor3f(1,1,1);
}
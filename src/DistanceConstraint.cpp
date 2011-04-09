#include "DistanceConstraint.h"
#include "Particle.h"

DistanceConstraint::DistanceConstraint(Particle* pA, Particle* pB) 
:a(pA)
,b(pB)
,Constraint()
{
	rest_length = (b->pos - a->pos).length();
	k = 0.1;
}

void DistanceConstraint::update(float dt) {
	ofVec3f dir = (b->tmp_pos - a->tmp_pos);
	float const len = dir.length();
	float const inv_mass = a->inv_mass + b->inv_mass;
	float const f = ((rest_length - len ) / inv_mass) * 0.1;

	dir *= (f / len); // normalize + multiply by force factor.
	if(!a->disabled) {
		a->tmp_pos -= (dir * a->inv_mass);
	}
	if(!b->disabled) {
		b->tmp_pos += (dir * b->inv_mass);
	}
	return;
}

void DistanceConstraint::draw() {
	glColor4f(0.3, 0.3, 0.3, 0.6f);
	glBegin(GL_LINES);
		glVertex3fv(a->pos.getPtr());
		glVertex3fv(b->pos.getPtr());
	glEnd();
	glColor3f(1,1,1);
}
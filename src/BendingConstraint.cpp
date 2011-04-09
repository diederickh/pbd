#include "BendingConstraint.h"
#include "Particle.h"
BendingConstraint::BendingConstraint(
	Particle* pA
	,Particle* pB
	,Particle* pC
)
:a(pA)
,b(pB)
,c(pC)
{
	w = a->inv_mass + c->inv_mass + (2*b->inv_mass);
	center = 0.3333 * (a->pos + b->pos + c->pos);
	rest_length = (a->pos - center).length();
	//cout << "rest length:" << rest_length << endl;
}

void BendingConstraint::draw() {
	glColor4f(1,1,0,0.8);
	glBegin(GL_TRIANGLES);
		glVertex3fv(&a->pos.x);
		glVertex3fv(&b->pos.x);
		glVertex3fv(&c->pos.x);
	glEnd();

	
	// draw "c"
	glColor3f(0,1,1);
	glPointSize(3);
	glBegin(GL_POINTS);
		glVertex3fv(&center.x);
	glEnd();
	glPointSize(1);

	glColor3f(1,1,1);
}


void BendingConstraint::update(float dt) {	
	float global_k = 10.01;
	int num_iter = 3;
	float k = 0;

	center = 0.3333 * (a->pos + b->pos + c->pos);
	ofVec3f dir_center = (center - b->pos);
	dist_center = dir_center.length();	

	float diff = 1.0f - ((global_k + rest_length) / dist_center);
	ofVec3f dir_force = dir_center * diff;
	
	ofVec3f fa = k * ((2.0f*a->inv_mass)/w) * dir_force;
	ofVec3f fb = k * ((4.0f*b->inv_mass)/w) * dir_force;
	ofVec3f fc = k * ((2.0f*c->inv_mass)/w) * dir_force;
	
	if(!a->disabled) {
		a->tmp_pos += fa;
	}
	if(!b->disabled) {
		b->tmp_pos -= fb;
	}
	if(!c->disabled) {
		c->tmp_pos += fc;
	}
	
	//cout << fa << endl;
	//cout << "diff:" <<  diff << ", dist_center:" << dist_center << " force:" << fa << " b.pos: " << b->pos << ", center:" << center<< "\n";
	
	
}

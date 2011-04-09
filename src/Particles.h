#pragma once
#include "ofMain.h"
class Particle;
class Constraint;

class Particles {
public:
	Particles();
	void addParticle(Particle* pParticle);
	void update(float dt = 0.02f);
	void draw();

	void addConstraint(Constraint* pConstraint);
	
	vector<Constraint*> constraints;
	vector<Particle*>particles;
	ofVec3f grav;
	float damping;
};
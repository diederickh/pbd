#pragma once
#include "ofMain.h"
class Particle;
class Constraint;

class Particles {
public:
	Particles();
	void addParticle(Particle* pParticle);
	void update();
	void draw();
	void addForce(ofVec3f oForce);
	void addConstraint(Constraint* pConstraint);
	
	vector<Constraint*> constraints;
	vector<Particle*>particles;
};
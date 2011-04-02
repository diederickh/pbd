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
	void addDisplacement(ofVec3f oDisplacement);
	void addConstraint(Constraint* pConstraint);
	
	vector<Constraint*> constraints;
	vector<Particle*>particles;
};
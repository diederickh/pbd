#pragma once
#include "ofMain.h"
#include "Constraint.h"
class Particle;
class BendingConstraint : public Constraint {
public:
	BendingConstraint(Particle* pParticleA, Particle* pParticleB, Particle* pParticleC);
	virtual void update(float dt = 0.02f);
	virtual void draw();
	
	Particle* a;
	Particle* b;
	Particle* c;
	float rest_length;
	float k;
	float w;
	ofVec3f center;
	float dist_center;
};
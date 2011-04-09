#pragma once
#include "Constraint.h"
class Particle;
class DistanceConstraint : public Constraint {
public:
	DistanceConstraint(Particle* pParticleA, Particle* pParticleB);
	virtual void update(float dt = 0.02f);
	virtual void draw();
	
	Particle* a;
	Particle* b;
	float rest_length;
	float k;
};
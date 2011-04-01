#pragma once
#include "Constraint.h"
class Particle;
class DistanceConstraint : public Constraint {
public:
	DistanceConstraint(Particle* pParticleA, Particle* pParticleB);
	virtual void update();
	virtual void draw();
	
	Particle* a;
	Particle* b;
	float rest_length;
	float k;
};
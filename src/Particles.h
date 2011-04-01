#pragma once
#include "ofMain.h"
class Particle;
class Particles {
public:
	Particles();
	void addParticle(Particle* pParticle);
	void update();
	void draw();
	
	vector<Particle*>particles;
};
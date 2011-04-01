#include "Particle.h"
#include "Particles.h"

Particles::Particles() {
}

void Particles::addParticle(Particle* pParticle) {
	particles.push_back(pParticle);
}

void Particles::draw() {
	vector<Particle*>::iterator it = particles.begin();
	while(it != particles.end()) {
		(*it)->draw();
		++it;
	}
}	

void Particles::update() {
	vector<Particle*>::iterator it = particles.begin();
	while(it != particles.end()) {
		(*it)->update();
		++it;
	}
}

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
		Particle* particle = (*it);

		// prediction step
		particle->velocity += particle->forces;
		particle->predicted_position = particle->position + particle->velocity;
		particle->forces.set(0,0,0);
		
		// add damping... (TODO)
		
		// generate constraints
		
		// solve constraints
		
		// update vertices
		++it;
	}
}

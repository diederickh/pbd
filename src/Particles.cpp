#include "Constraint.h"
#include "Particle.h"
#include "Particles.h"

Particles::Particles() {
}

void Particles::addParticle(Particle* pParticle) {
	particles.push_back(pParticle);
}

void Particles::addConstraint(Constraint* pConstraint) {
	constraints.push_back(pConstraint);
}

// add a vec3 force.
// -----------------------------------
void Particles::addForce(ofVec3f oForce) {
	vector<Particle*>::iterator it = particles.begin();
	while(it != particles.end()) {
		(*it)->addForce(oForce);
		++it;
	}
}


// draw the particles (using simple GL_POIINTS now 
// ------------------------------------------------
void Particles::draw() {

	// draw constraints.
	{
		vector<Constraint*>::iterator it = constraints.begin();
		while(it != constraints.end()) {
			(*it)->draw();
			++it; 
		}
	}

	// draw particles.
	{
		vector<Particle*>::iterator it = particles.begin();
		while(it != particles.end()) {
			(*it)->draw();
			++it;
		}
	}
}	


// Solve
// -----------------------------------
void Particles::update() {
	// project constraints.
	{
		vector<Constraint*>::iterator it = constraints.begin();
		while(it != constraints.end()) {
			(*it)->update();
			++it;
		}
	}	
	
	// project position.
	{
		vector<Particle*>::iterator it = particles.begin();
		while(it != particles.end()) {
			Particle& particle = **it;

			// prediction step
			particle.velocity += particle.forces;
			particle.predicted_position = particle.position + particle.velocity;
			
			// add displacement
			// ---------------------------------
			// ---------------------------------
			
			// clear forces.
			particle.forces.set(0,0,0);
			
			++it;
		}
	}
}

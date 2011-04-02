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
void Particles::addDisplacement(ofVec3f oDisplacement) {
	vector<Particle*>::iterator it = particles.begin();
	while(it != particles.end()) {
		(*it)->addDisplacement(oDisplacement);
		++it;
	}
}

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
	float dt = 1;
	// project position:
	{
		vector<Particle*>::iterator it = particles.begin();
		while(it != particles.end()) {
			Particle& particle = **it;

			// prediction step
			particle.velocity += particle.forces;
			particle.velocity += particle.displacement;
			particle.predicted_position = particle.position + (particle.velocity * dt);

			particle.displacement.set(0,0,0);
			particle.forces.set(0,0,0);
			++it;
		}
	}
	
	// project constraints.
	{
		vector<Constraint*>::iterator it = constraints.begin();
		while(it != constraints.end()) {
			(*it)->update();
			++it;
		}
	}	

	// update position.
	{
		vector<Particle*>::iterator it = particles.begin();
		while(it != particles.end()) {
			Particle& particle = **it;
			// add displacement
			// ---------------------------------
			// ---------------------------------
			particle.velocity = (particle.predicted_position - particle.position)/dt;
			particle.position = particle.predicted_position;
			particle.velocity *= 0.98;
			++it;
		}
	}

	

}

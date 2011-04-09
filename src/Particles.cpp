#include "Constraint.h"
#include "Particle.h"
#include "Particles.h"

Particles::Particles()
:grav(.0f,.0f, .0f) // 9.82f
,damping(0.99f)
{
}

void Particles::addParticle(Particle* pParticle) {
	particles.push_back(pParticle);
}

void Particles::addConstraint(Constraint* pConstraint) {
	constraints.push_back(pConstraint);
}

// draw the particles (using simple GL_POINTS now 
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
void Particles::update(float dt) {
	float inv_dt = 1/dt;

	// predict locations (semi implicit euler
	for(int i = 0; i < particles.size(); ++i) {
		Particle& p = *(particles[i]);
		if(p.disabled) {
			p.tmp_pos = p.pos;
		}
		else {

			p.vel += grav * dt;
			p.tmp_pos = p.pos + (p.vel * damping * dt);
		}
	}	 
	
	// constraints.
	for(int j = 0; j < 3; ++j) {
		for(int i = 0; i < constraints.size(); ++i) {
			constraints.at(i)->update(dt);
		}
	}
			
	// update velocity+pos
	for(int i = 0; i < particles.size(); ++i) {
		Particle&p = *particles[i];
		if(p.disabled) {
			continue;
		}
		p.vel = (p.tmp_pos - p.pos) * inv_dt;
		p.pos = p.tmp_pos;
		p.tmp_pos.set(0,0,0);
	}

}

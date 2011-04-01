#pragma once
#include "ofMain.h"

class Particle {
public:
	Particle(ofVec3f oPosition, float nMass);
	
	void addForce(ofVec3f oForce);
	void draw();
	void update();
	
	ofVec3f forces;
	ofVec3f predicted_position;
	ofVec3f position;
	ofVec3f velocity;
	float mass;
	float inverse_mass;
};

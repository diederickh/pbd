#pragma once
#include "ofMain.h"

class Particle {
public:
	Particle(ofVec3f oPosition, float nMass);
	
	void addDisplacement(ofVec3f oDisplacement);
	void draw();
	void update();
	
	ofVec3f displacement;
	ofVec3f predicted_position;
	ofVec3f position;
	ofVec3f velocity;
	float mass;
	float inverse_mass;
};

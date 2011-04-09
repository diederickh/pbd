#pragma once
#include "ofMain.h"

class Particle {
public:
	Particle(ofVec3f oPosition, float nMass);
	void draw();
	void update();
	
	ofVec3f tmp_pos;
	ofVec3f pos;
	ofVec3f vel;
	float mass;
	float inv_mass;
	bool disabled;
};

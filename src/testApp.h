#pragma once

#include "ofMain.h"
#include "Particles.h"
#include "Particle.h"
#include "DistanceConstraint.h"
#include "Cloth.h"
#include "ofxOpenGLMath.h"
#include "ofxTweakbarIncludes.h"

using namespace glm;
class testApp : public ofBaseApp{

	public:
		testApp();
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		Particles particles;
		bool follow;
		bool record;
		int frame_num;
		Cloth cloth;	
		
		bool test_force;
		ofxTweakbar* settings;
		
		mat4 persp;
		mat4 cam;
		quat rot;
};

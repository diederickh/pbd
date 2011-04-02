#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(45);
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofBackground(0xfb, 0xec, 0xc0);
	follow = false;
	record = false;
	frame_num = 0;
}

//--------------------------------------------------------------
void testApp::update(){
	particles.addDisplacement(ofVec3f(0,0.1,0));
	for(int i = 0; i < 5; ++i) particles.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	particles.draw();
	if(record) {
		char buf[512];
		sprintf(buf, "pbd-%04d.png", frame_num);
		ofSaveScreen(buf);
		++frame_num;
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'f') {
		follow = !follow;
	}
	else if(key == 'r') {
		record = !record;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if(particles.particles.size() >= 1 && follow) {
		particles.particles.at(0)->position.set(x,y,0);
		particles.particles.at(0)->displacement.set(0,0,0);
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	particles.addParticle(new Particle(ofVec3f(x,y, 0), ofRandom(0.4,2.0)));
	int size = particles.particles.size();
	if(size > 1) {
		DistanceConstraint* dist_constraint = new DistanceConstraint(
			 particles.particles.at(size-2)
			,particles.particles.at(size-1)
		);
		particles.addConstraint(dist_constraint);
	}
	else {
		particles.particles.back()->inverse_mass = 0;
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
#include "testApp.h"

testApp::testApp()
:cloth(60,40,20)
,cloth_gl(cloth)
{
}

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(65);
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofBackground(0xfb, 0xec, 0xc0);
	ofBackground(0x33, 0x33, 0x33);
	debug = true;
	follow = false;
	record = false;
	test_force = false;
	frame_num = 0;
	
	settings = ofxTweakbars::create("settings","settings");
	settings->addQuat4f("quater", &rot.x)->setLabel("Rotation");
	settings->load();
	
	cam = translate(cam, vec3(-(float)cloth.width*0.25,(float)cloth.height*0.25 + 100,-900));
	persp = perspective(45.0f, (float)ofGetWidth()/ofGetHeight(), 1.0f, 4000.0f);
	cloth_gl.setup();
}

//--------------------------------------------------------------
void testApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	particles.update(0.02);
	if(test_force && cloth.particles.particles.size() > 100) {

		ofVec3f f(0,0,-70);
		for(int i = 8; i < 10; ++i) {
			for(int j = 8; j < 10; ++j) {
				cloth.getAt(i,j).addForce(f);
			}
		}
		for(int i = 20; i < 28; ++i) {
			for(int j = 8; j < 16; ++j) {
				cloth.getAt(i,j).addForce(f*-1);
			}
		}

	}
	
	cloth.update();
	cloth_gl.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(persp));
	glMatrixMode(GL_MODELVIEW);
	mat4 qrot = cam * mat4_cast(rot);
	glLoadMatrixf(value_ptr(qrot));
	glEnable(GL_DEPTH_TEST);
	if(debug){
		cloth.draw();	
	}
	else {
		cloth_gl.draw();
	}
	particles.draw();
	if(record) {
		char buf[512];
		sprintf(buf, "pbd-%04d.png", frame_num);
		ofSaveScreen(buf);
		++frame_num;
	}

	ofxTweakbars::draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'f') {
		follow = !follow;
	}
	else if(key == 'r') {
		record = !record;
	}
	else if (key == 'i') {
		// invert grav.
		if(cloth.particles.grav.z < 0 || cloth.particles.grav.z == 0) {
			cloth.particles.grav.z	= 34;
		}
		else {
			cloth.particles.grav.z = -34;
		}
	}
	else if(key == 't') {
		test_force = !test_force;
	}
	else if(key == 'd') {
		debug = !debug;
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if(particles.particles.size() >= 1 && follow) {
		particles.particles.at(0)->pos.set(x,y,0);
		//particles.particles.at(0)->displacement.set(0,0,0);
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
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
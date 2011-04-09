#include "testApp.h"

testApp::testApp()
:cloth(20,20,10)
{
}

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(65);
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofBackground(0xfb, 0xec, 0xc0);
	ofBackground(0x33, 0x33, 0x33);
	follow = false;
	record = false;
	test_force = false;
	frame_num = 0;
	
	settings = ofxTweakbars::create("settings","settings");
	settings->addQuat4f("quater", &rot.x)->setLabel("Rotation");
	settings->load();
	
	cam = translate(cam, vec3(-(float)cloth.width*0.25,(float)cloth.height*0.25 + 100,-900));
	persp = perspective(45.0f, (float)ofGetWidth()/ofGetHeight(), 1.0f, 4000.0f);
}

//--------------------------------------------------------------
void testApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	particles.update(0.02);
	cloth.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(persp));
	glMatrixMode(GL_MODELVIEW);
	mat4 qrot = cam * mat4_cast(rot);
	glLoadMatrixf(value_ptr(qrot));
	cloth.draw();	
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
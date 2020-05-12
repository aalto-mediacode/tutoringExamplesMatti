#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetBackgroundAuto(false);
	pos = { ofRandomWidth(), ofRandomHeight() };
	vel = { 0.0,0.0 };
	acc = { 0.0,0.0 };
	offsets = { ofRandom(1000), ofRandom(1000) };
}

//--------------------------------------------------------------
void ofApp::update() {
	float timer = ofGetElapsedTimef();
	float mult = 10.0;
	noise = { mult*ofSignedNoise(offsets.x + timer), mult*ofSignedNoise(offsets.y + timer) };

	if (ofGetMousePressed()) {
		target = { mouseX, mouseY };
	}
	else {
		target = { ofGetWidth() / 2, ofGetHeight() / 2 };
	}
	
	// get the direction vector
	target = target - pos;

	// normalize the vector
	glm::normalize(target);

	//scale the vector
	target *= 0.001;

	acc = target;

	vel = vel + acc;
	pos = pos + vel;
    pos = pos + noise;

	if (glm::length(vel) > 5.0) {
		vel = glm::normalize(vel) * 5.0;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::gray, ofColor::black);
	ofDrawCircle(pos, 30);
	//ofDrawRectangle(pos, 1, 1);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

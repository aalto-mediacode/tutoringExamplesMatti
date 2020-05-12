#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    kinect.open();
    ofxKinectV2::Settings ksettings;
    ksettings.enableRGB = true;
    ksettings.enableIR = true;
    ksettings.enableDepth = true;
    ksettings.enableRGBRegistration = true;
    ksettings.enableDepthRegistration = true;
    ksettings.config.MinDepth = 0.5;
    ksettings.config.MaxDepth = 8.0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    if(kinect.isFrameNew()){
        depthTexture.loadData(kinect.getDepthPixels());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    depthTexture.draw(0,0);
}

void ofApp::exit(){
    kinect.close();
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

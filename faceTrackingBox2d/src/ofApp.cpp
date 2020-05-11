#include "ofApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    vector<ofVideoDevice> devices = cam.listDevices();
    
    for(int i=0; i < devices.size(); i++){
        ofLogNotice() << devices[i].id << ":" << devices[i].deviceName;
    }
    cam.setDeviceID(2);
    cam.initGrabber(640, 360);
    
    tracker.setup();
    
    //box2d
    box2d.init();
    box2d.setGravity(0, 100);
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    anchor.setup(box2d.getWorld(), 20, ofGetHeight()/2, 4);
    
    // first we add just a few circles
    for (int i=0; i<3; i++) {
        auto circle = make_shared<ofxBox2dCircle>();
        circle->setPhysics(20.0, 0.13, 0.2);
        //circle->setPh
        circle->setup(box2d.getWorld(), ofGetWidth()/2, 100+(i*20), 8);
        circles.push_back(circle);
    }
    // now connect each circle with a joint
    for (int i=0; i<circles.size(); i++) {
        
        auto joint = make_shared<ofxBox2dJoint>(box2d.getWorld(), i == 0 ? anchor.body : circles[i-1]->body, circles[i]->body);
        
        
        
        joint->setLength(15);
        joint->setDamping(0.5);
        joints.push_back(joint);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()){
        tracker.update(toCv(cam));
        if(tracker.getFound()){
            facePoints = tracker.getImagePoints();
            anchor.setPosition(facePoints[35].x, facePoints[35].y);
        }
    }
    box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    cam.draw(0,0);
    if(tracker.getFound()){
//        tracker.draw();
        for(int i=0; i < facePoints.size(); i++){
//            ofDrawCircle(facePoints[i], 3);
//            ofDrawBitmapString(i, facePoints[i]);
        }
    }
//    anchor.draw();
    
    for(auto &circle : circles) {
        ofFill();
        ofSetHexColor(0x01b1f2);
        ofSetLineWidth(5);
//        circle->draw();
    }
    
    for(auto &joint : joints) {
        ofSetColor(60,200,10,100);;
        ofSetLineWidth(5);
        joint->draw();
    }
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

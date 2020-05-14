#include "ofApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    vector<ofVideoDevice> devices = cam.listDevices();
    
    for(int i=0; i < devices.size(); i++){
        ofLogNotice() << devices[i].id << ":" << devices[i].deviceName;
    }
    
    cam.setDeviceID(3);
    cam.initGrabber(1280, 720);
    
    tracker.setup();
    
    // text
    string loremIpsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum rutrum ligula sed gravida bibendum. Morbi vitae neque at risus suscipit placerat. Maecenas pulvinar ante eu eros euismod, non congue eros scelerisque. Etiam imperdiet mauris ante, hendrerit lacinia risus pulvinar in. Fusce varius in ipsum sed ullamcorper. Aenean condimentum nisi eu neque posuere, ac accumsan dolor tempor. Phasellus in risus sit amet turpis fringilla tempus et eget.";
    
    // split into words
    words = ofSplitString(loremIpsum, " ");
    
    font.load("Courier New Bold", 50);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()){
        tracker.update(toCv(cam));
        if(tracker.getFound()){
            facePoints = tracker.getImagePoints();
            tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //cam.draw(0,0);
    ofBackgroundGradient(ofColor::gray, ofColor::black);
    ofSetColor(0);
    
    ofPixelsRef pixelsRef = cam.getPixels();
    
    if(tracker.getFound()){
        //tracker.draw();
        for(int i=0; i < facePoints.size(); i++){
            
            float lightness = pixelsRef.getColor(facePoints[i].x, facePoints[i].y).getLightness();
            float scale = ofMap(lightness, 0, 255, 0.7,  0.005 );
           
            ofPushMatrix();
            ofTranslate(facePoints[i]);
            ofScale(scale);
            font.drawString(words[i], 0, 0);
            ofPopMatrix();
            
            //ofDrawCircle(facePoints[i], 3);
            //ofDrawBitmapString(i, facePoints[i]);
        }
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

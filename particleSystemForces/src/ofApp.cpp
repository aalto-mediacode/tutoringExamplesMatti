#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(100);
    ofBackground(0);
    image.load("stars.png");
    
    int w = image.getWidth();
    int h = image.getHeight();
    
    //set up the particles
    
    int skip = 50;
    for(int x=0; x<w; x=x+skip){
        for(int y=0; y<h; y=y+skip){
            glm::vec2 tempVector = {x,y};
            ofColor tempColor = image.getColor(x, y);;
            
            Particle newParticle;                   //1. create a new particle
            newParticle.setup(tempVector,tempColor); //2. run its setup() function
            myParticles.push_back(newParticle);      //3. add it to the vector
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //update the particle
    for(int i=0;i<myParticles.size();i++){
        myParticles[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i=0;i<myParticles.size();i++){
        myParticles[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g'){
        for(int i=0;i<myParticles.size();i++){
            myParticles[i].addGravity();
        }
    }

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

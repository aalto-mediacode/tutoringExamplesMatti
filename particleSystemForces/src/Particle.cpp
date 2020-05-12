#include "Particle.hpp"

void Particle::setup(glm::vec2 originV, ofColor c){
    //posV is position vector
    posV=originV;
    col = c;
    
    //velV is velocity vector
    velV={ofRandom(-2.0,2.0),ofRandom(-2.0,2.0)};
    //velV={0.0,0.0};
    //accelV={0.0,0.1};//accelV is the acceleration vector
    radius = 10;
}

void Particle::update(){
    
   
    if(posV.x >= ofGetWidth() - radius){
        velV.x*=-1;
        posV.x = ofGetWidth() - radius;
    }
    
    if(posV.x <= 0 + radius){
        velV.x*=-1;
        posV.x = radius;
    }
    
    if(posV.y >= ofGetHeight() - radius){
        velV.y*=-1;
        posV.y = ofGetHeight() -radius;
    }
    
    if(posV.y <= 0 - radius){
        velV.y*=-1;
        posV.y = radius;
    }
    
    velV+=accelV;//increment velocity with acceleration
    posV+=velV;//same as posV = posV+velV
}

void Particle::addGravity(){
    accelV={0.0,1.0};
}

void Particle::draw(){
    ofSetColor(col);
    ofDrawCircle(posV, radius);
}

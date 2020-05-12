#pragma once

#include "ofMain.h"

class Particle{

    public:
        void setup(glm::vec2 originV, ofColor c);
        void update();
        void draw();
    void addGravity();
    
    glm::vec2 posV;
    glm::vec2 velV;
    glm::vec2 accelV;
    ofColor col;
    int radius;
    ofVec2f point;
};

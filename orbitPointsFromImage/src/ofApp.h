#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // reset the mesh:
    void resetMeshPressed();
    
    ofMesh mesh;
    ofImage image;
    ofEasyCam cam;
    vector<glm::vec3> offsets;
    int numVerts;
    
    // gui stuff
    ofxPanel gui;
    ofxIntSlider pointSize;
    ofxFloatSlider displacementScale;
    ofxFloatSlider timeScale;
    ofxButton resetMesh;
    ofxToggle toggleOrbiting;
    
    // We are going to use these to allow us to toggle orbiting on and off
    ofMesh meshCopy;
    bool orbiting;
    float startOrbitTime;
    
    // These variables will let us store the polar coordinates of each vertex
    vector<float> distances;
    vector<float> angles;
    glm::vec3 meshCentroid;
    
    float orbitTimer;
};

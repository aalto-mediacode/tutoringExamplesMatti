#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Add this line to explicitly set the framerate to 60 frames per second:
    ofSetFrameRate(60);
    
    // load image
    image.load("stars.png");
    
    // mesh
    mesh.setMode(OF_PRIMITIVE_POINTS);
    mesh.enableColors();
    // We are going to be using indices this time
    mesh.enableIndices();
    
    //GL settings
    glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
    
    // get image width and height
    int w = image.getWidth();
    int h = image.getHeight();
    
    // don't use every pixel in the image. let's skip some pixels
    // if the skip = 5, we only use every 5th pixel
    int skip = 5;
    
    for(int x=0; x<w; x=x+skip){
        for (int y=0; y<h; y=y+skip) {
            
            // get the color of the pixel at x, y
            // note that we are going backwards on the y to get the image oriented correctly
            ofColor c = image.getColor(x, (h-1)-y);
            
            // create a vector to store the coordinate. z is 0.0 to start for all vertices
            glm::vec3 pos(x, y, 0.0);
            
            //add the vertex to the mesh and and use color from the image
            mesh.addVertex(pos);
            mesh.addColor(c);
            
            // This will create a ofVec3f with 3 random values, which
            // will allow us to move the x, y and z coordinates of
            // each vertex independently
            offsets.push_back(glm::vec3(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            
        }
    }
    
    numVerts = mesh.getNumVertices();
    ofLogNotice() << "vertices:" << numVerts;
    
    // We need to calculate our center point for the mesh
    // ofMesh has a method called getCentroid() that will
    // find the average location over all of our vertices
    //    http://en.wikipedia.org/wiki/Centroid
    meshCentroid = mesh.getCentroid();

    // Now that we know our centroid, we need to know the polar coordinates
    // (distance and angle) of each vertex relative to that center point.
    // We've found the distance between points before, but what about the angle?
    // This is where atan2 comes in.  atan2(y, x) takes an x and y value and returns
    // the angle relative to the origin (0,0).  If we want the angle between two
    // points (x1, y1) and (x2, y2) then we just need to use atan2(y2-y1, x2-x1).
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        float distance = vert.distance(meshCentroid);
        float angle = atan2(vert.y-meshCentroid.y, vert.x-meshCentroid.x);
        distances.push_back(distance);
        angles.push_back(angle);
    }

    // These variables will allow us to toggle orbiting on and off
    orbiting = false;
    startOrbitTime = 0.0;
    meshCopy = mesh; // Store a copy of the mesh, so that we can reload the original state
    
    
    //setup the gui
    gui.setup(); // most of the time you don't need a name
    gui.add(pointSize.setup("GL point size", 8, 1, 20));
    gui.add(displacementScale.setup("displacement", 1.0, 0.1, 20.0));
    gui.add(timeScale.setup("time scale", 1.0, 0.1, 10.0));
    gui.add(toggleOrbiting.setup("orbit",false));
    gui.add(resetMesh.setup("reset mesh"));
    resetMesh.addListener(this, &ofApp::resetMeshPressed);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(toggleOrbiting){
        orbiting=true;
        // add to the orbit timer
        orbitTimer += 0.01;
    }else{
        orbiting=false;
    }
    
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        
        if (orbiting) {
            float distance = distances[i];
            float angle = angles[i];
            
            
            // Lets adjust the speed of the orbits such that things that are closer to
            // the center rotate faster than things that are more distant
            float speed = ofMap(distance, 0, image.getWidth()/2, 1.0, 0.1, true);
            
            // To find the angular rotation of our vertex, we use the current time and
            // the starting angular rotation
            float rotatedAngle = orbitTimer * speed + angle;
            
            // Remember that our distances are calculated relative to the centroid
            // of the mesh, so we need to shift everything back to screen
            // coordinates by adding the x and y of the centroid
            vert.x = distance * cos(rotatedAngle) + meshCentroid.x;
            vert.y = distance * sin(rotatedAngle) + meshCentroid.y;
    
        }

        
        // NOISE
        float time = ofGetElapsedTimef();
        glm::vec3 timeOffsets = offsets[i];
        // A typical design pattern for using Perlin noise uses a couple parameters:
        // ofSignedNoise(time*timeScale+timeOffset)*displacementScale
        //     ofSignedNoise(time) gives us noise values that change smoothly over
        //         time
        //     ofSignedNoise(time*timeScale) allows us to control the smoothness of
        //         our noise (smaller timeScale, smoother values)
        //     ofSignedNoise(time+timeOffset) allows us to use the same Perlin noise
        //         function to control multiple things and have them look as if they
        //         are moving independently
        //     ofSignedNoise(time)*displacementScale allows us to change the bounds
        //         of the noise from [-1, 1] to whatever we want
        // Combine all of those parameters together, and you've got some nice
        // control over your noise
        
        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
        
        mesh.setVertex(i, vert);
    }
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::gray, ofColor::black);
    //image.draw(0,0);
    
    ofEnableDepthTest();
    glPointSize(pointSize); // make the points bigger
    cam.begin();
    ofPushMatrix();
    ofTranslate(-image.getWidth()/2, -image.getHeight()/2);
    mesh.draw();
    ofPopMatrix();
    cam.end();
    ofDisableDepthTest();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::resetMeshPressed(){
    orbitTimer = 0.0;
    mesh = meshCopy; // This restores the mesh to its original values
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

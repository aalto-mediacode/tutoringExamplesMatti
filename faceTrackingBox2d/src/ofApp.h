#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"
#include "ofxBox2d.h"

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
    
        ofVideoGrabber cam;
        ofxFaceTracker tracker;
        vector<glm::vec2> facePoints;
    
        ofxBox2d                                    box2d;       //    the box2d world
        ofxBox2dCircle                              anchor;      //    fixed anchor
        vector        <shared_ptr<ofxBox2dCircle>>  circles;     //    default box2d circles
        vector        <shared_ptr<ofxBox2dJoint>>   joints;      //    joints
		
};

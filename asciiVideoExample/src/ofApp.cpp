#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
    ofBackground(255);

    // try to grab at this size
	camWidth = 1280;
	camHeight = 720;
	
    vidGrabber.setDeviceID(3);
	vidGrabber.setVerbose(true);
	vidGrabber.setup(camWidth,camHeight);

	font.load("Courier New Bold.ttf", 50);
    
    // this set of characters comes from the Ascii Video Processing example by Ben Fry,
	// changed order slightly to work better for mapping
    asciiCharacters =  string("  ..,,,'''``--_:;^^**""=+<>iv%&xclrs)/){}I?!][1taeo7zjLunT#@JCwfy325Fp6mqSghVd4EgXPGZbYkOA8U$KHDBWNMR0Q");
   
    //asciiCharacters =  string("this set of characters comes from the Ascii Video Processing example by Ben Fry,");
	
    
    
    
    words = {
        " ",
        " ",
        " ",
        "this",
        "is",
        "red",
        "apple",
        "blue",
        " ",
        " ",
        " ",
        " ",
        " ",
        " "
    };
    
    
    ofEnableAlphaBlending();
}


//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
    // change background video alpha value based on the cursor's x-position
    float videoAlphaValue = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
    
    // set a white fill color with the alpha generated above
    ofSetColor(255,255,255,videoAlphaValue);

    // draw the raw video frame with the alpha value generated above
    //vidGrabber.draw(0,0);

	ofPixelsRef pixelsRef = vidGrabber.getPixels();
    
    ofSetColor(0);

    for (int i = 0; i < camWidth; i+= 10){
        for (int j = 0; j < camHeight; j+= 10){
            
            
            
            // get the pixel and its lightness (lightness is the average of its RGB values)
            float lightness = pixelsRef.getColor(i,j).getLightness();
            if(lightness > 80 && lightness < 200){
                
                // calculate the index of the character from our asciiCharacters array
                int character = powf( ofMap(lightness, 255, 0, 0, 1), 2.5) * asciiCharacters.size();
                //int word = ofMap(lightness, 0, 255, 0, words.size());
                
                
                
                float scale = ofMap(lightness, 130, 200, 0.7,  0.005 );
                ofPushMatrix();
                ofTranslate(i, j);
                ofScale(scale);
                // draw the character at the correct location
                font.drawString(ofToString(asciiCharacters[character]), 0, 0);
                //font.drawString(words[word], 0,0);
                ofPopMatrix();
            }
        }
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
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

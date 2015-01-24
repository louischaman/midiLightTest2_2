#pragma once

#include "ofMain.h"
#include "ofBaseLight.h"

class ofToggleLight: public ofBaseLight{
public:
    //constructor
    ofToggleLight(){bTriggered = false;};
    //destructor
    ~ofToggleLight(){};

    //methods
    void draw(){
        ofPushStyle();
            ofFill();
            if(bState && bTriggered) ofSetColor(255);
            else ofSetColor(0);
            ofRect(xPos, yPos, boxSize, boxSize);

            ofNoFill();
            ofSetColor(240);
            ofRect(xPos, yPos, boxSize, boxSize);

            ofSetColor(225);
            ofDrawBitmapString("toggle " + ofToString(lightID,0), xPos, yPos + boxSize+16);
        ofPopStyle();
    };

    //friend class ofLightManager;
    bool bTriggered;
};

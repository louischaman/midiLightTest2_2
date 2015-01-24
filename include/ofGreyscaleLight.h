//extends ofBaseLight to provide greyscale features
#pragma once
#include "ofBaseLight.h"
#include "ofLightChannel.h"

class ofGreyscaleLight: public ofBaseLight{
public:
    //constructor
    ofGreyscaleLight(){};
    //destructor
    ~ofGreyscaleLight(){};
    //friend so that only lightControl has access
    //friend class ofLightManager;

    ofLightChannel greyscale;

    //interface
    void flashTo(float level){greyscale.flashTo(level); };
    void fadeTo(float level){greyscale.fadeTo(level); };
    void setDamping(float level){greyscale.setDamping(level); };
    void setMaxLevel(float level){greyscale.setMaxLevel(level); };

    float returnDamping(){greyscale.returnDamping();};
    float returnMaxLevel(){greyscale.returnMaxLevel();};

    int output(){
        // if toggle is true, maps current level between 0 and max level and casts as an int
        if (bState){
            return greyscale.output();
        } else return 0;
    };

    void draw(){
        ofPushStyle();
            ofFill();
            ofSetColor(output());
            ofRect(xPos, yPos, boxSize, boxSize);

            ofNoFill();
            ofSetColor(240);
            ofRect(xPos, yPos, boxSize, boxSize);

            ofSetColor(225);
            ofDrawBitmapString("gScale " + ofToString(lightID,0), xPos, yPos + boxSize+16);
        ofPopStyle();
    };
};

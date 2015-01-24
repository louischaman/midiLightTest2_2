#pragma once
#include "ofMain.h"

class ofLightChannel{
public:
    //constructor destructor
    ofLightChannel();
    ~ofLightChannel();

    //methods
    void flashTo(float level);
    void fadeTo(float level);
    void setDamping(float damping);
    void setMaxLevel(float level);

    float returnDamping();
    float returnMaxLevel();

    int output();

private:
    void updateLevel();

    //variables
    float targetLevel;
    float currentLevel;
    float maxLevel;

    int outputLevel;
    float damping;

};

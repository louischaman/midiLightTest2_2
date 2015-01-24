#include "ofLightChannel.h"

ofLightChannel::ofLightChannel(){
    currentLevel = 0.0;
    outputLevel = 0;
    targetLevel = 0.0;
    maxLevel = 255;
    damping = 0.3;
}

ofLightChannel::~ofLightChannel(){

}

void ofLightChannel::flashTo(float _level){
    currentLevel = _level;
}

void ofLightChannel::fadeTo(float _level){
    targetLevel = _level;
    updateLevel();
}

void ofLightChannel::setDamping(float level){
    damping = level;
}

void ofLightChannel::setMaxLevel(float level){
    maxLevel = ofMap(level, 0.0, 1.0, 0.0, 255.0, true);
}

float ofLightChannel::returnDamping(){
    return damping;
}

float ofLightChannel::returnMaxLevel(){
    return ofMap(maxLevel, 0.0, 255.0, 0.0, 1.0, true);
}

int ofLightChannel::output(){
    outputLevel = static_cast<int>(ofMap(currentLevel, 0.0, 1.0, 0.0, maxLevel, true));
    return outputLevel;
}

// updates level of light using exponential moving average filter
void ofLightChannel::updateLevel(){
    currentLevel = currentLevel + damping*(targetLevel-currentLevel);
}

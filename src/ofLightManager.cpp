#include "ofLightManager.h"

//constructor
ofLightManager::ofLightManager(){

}
// destructor
ofLightManager::~ofLightManager(){
    for(vector<ofToggleLight *>::iterator it = tLights.begin(); it != tLights.end(); ++it){
        ofToggleLight *l = *it;
        delete l;
    }
    for(vector<ofGreyscaleLight *>::iterator it = gLights.begin(); it != gLights.end(); ++it){
        ofGreyscaleLight *l = *it;
        delete l;
    }

}

//---------------------------------------------------
//INTERFACE
//---------------------------------------------------
// COMMON
// setup
void ofLightManager::setup(int _nToggle, int _nGreyscale){
    // set no of lights
    nToggle = _nToggle;
    nGreyscale = _nGreyscale;
    nLights = nToggle + nGreyscale;

    // initialize variables
    boxSize = 100;
    xPos = 32;
    yPos = 48;

    bLightsTriggered.assign(nToggle, false);

    lightLevels.assign(nGreyscale, 0.0);
    outputLevels.assign(nGreyscale, 0.0);

    // create toggleLights
    for (int i = 0; i < nToggle; i++){
        xPos = (i%2)*116+32;

        ofToggleLight* light = new ofToggleLight();
        light->setup(xPos, yPos, boxSize, i);
        tLights.push_back(light);

        yPos += (i%2)*132;
    }

    //create grayscaleLights
    for (int i = nToggle; i < nLights; i++){
        xPos = (i%2)*116+32;

        ofGreyscaleLight* light = new ofGreyscaleLight();
        light->setup(xPos, yPos, boxSize, i);
        gLights.push_back(light);

        yPos += (i%2)*132;
    }
}
//---------------------------------------------------
//
void ofLightManager::draw(int lightType, int lightID){
    switch (lightType){
        case 0:
            tLights[lightID]->draw();
            break;
        case 1:
            gLights[lightID]->draw();
            break;

        default:
            break;
    }
}
//---------------------------------------------------
//
bool ofLightManager::bReturnState(int lightType, int lightID){
    switch (lightType){
        case 0:
            return tLights[lightID]->bReturnState();
            break;
        case 1:
            return gLights[lightID]->bReturnState();
            break;

        default:
            break;
    }
}
//---------------------------------------------------
//
void ofLightManager::drawAll(){
    for (int i = 0; i < nToggle; i++){
        draw(0, i);
    }
    for (int i = 0; i < nGreyscale; i++){
        draw(1, i);
    }
}
//---------------------------------------------------
//
vector<bool> ofLightManager::bReturnAllStates(){
    vector<bool> bStates;
    bStates.assign(nLights, false);
    for (int i = 0; i < nToggle; i++){
        bStates[i] = bReturnState(0, i);
    }
    for (int i = 0; i < nGreyscale; i++){
        bStates[i+nToggle] = bReturnState(1, i);
    }
    return bStates;
}
//---------------------------------------------------
// TOGGLE LIGHTS
//---------------------------------------------------
//
void ofLightManager::setLightsTriggered(vector<bool> _bLightsTriggered){
    bLightsTriggered = _bLightsTriggered;
}
/*void ofLightManager::setLightsTriggered(ofLightSceneManager &scenes){
    bLightsTriggered = scenes.bTriggered;
}*/
//---------------------------------------------------
//
void ofLightManager::toggleTrigger(int lightID){
    tLights[lightID]->bTriggered = !(tLights[lightID]->bTriggered);
}
//---------------------------------------------------
//
void ofLightManager::setTrigger(int lightID, bool bTriggered){
    tLights[lightID]->bTriggered = bTriggered;
}
//---------------------------------------------------
//
bool ofLightManager::bReturnTrigger(int lightID){
    return tLights[lightID]->bTriggered;

}
//---------------------------------------------------
//
void ofLightManager::setAllTrigger(){
    for(int i = 0; i < nToggle; i++){
        setTrigger(i, bLightsTriggered[i]);
    }
}
//---------------------------------------------------
//
vector<bool>ofLightManager::bReturnAllTrigger(){
    vector<bool> bTriggers;
    bTriggers.assign(nToggle, false);

    for(int i = 0; i < nToggle; i++){
        bTriggers[i] = bReturnTrigger(i);
    }
    return bTriggers;
}
//---------------------------------------------------
// GRAYSCALE
//---------------------------------------------------
//
void ofLightManager::setLevels(vector<float> _lightLevels){
    lightLevels = _lightLevels;
}
//---------------------------------------------------
//
void ofLightManager::flashTo(int lightID, float level){
    gLights[lightID]->flashTo(level);
}
//---------------------------------------------------
//
void ofLightManager::fadeTo(int lightID, float level){
    gLights[lightID]->fadeTo(level);
}
//---------------------------------------------------
//
void ofLightManager::setDamping(int lightID, float level){
    gLights[lightID]->setDamping(level);
}
//---------------------------------------------------
//
void ofLightManager::setMaxLevel(int lightID, float level){
    gLights[lightID]->setMaxLevel(level);
}
//---------------------------------------------------
//
int ofLightManager::returnLevel(int lightID){
    return gLights[lightID]->output();
}
//---------------------------------------------------
//
float ofLightManager::returnDamping(int lightID){
    return gLights[lightID]->returnDamping();
}
//---------------------------------------------------
//
float ofLightManager::returnMaxLevel(int lightID){
    return gLights[lightID]->returnMaxLevel();
}
//---------------------------------------------------
//
void ofLightManager::setAllDamping(float damping){
    for(int i = 0; i < nGreyscale; i++){
        setDamping(i, damping);
    }
}
//---------------------------------------------------
//
void ofLightManager::setAllMaxLevel(float level){
    for(int i = 0; i < nGreyscale; i++){
        setMaxLevel(i, level);
    }
}
//---------------------------------------------------
//
vector<int> ofLightManager::returnAllLevels(){
    vector<int> levels;
    levels.assign(nGreyscale, 0);

    for(int i = 0; i < nGreyscale; i++){
        levels[i] = returnLevel(i);
    }
    return levels;
}
//---------------------------------------------------
//
void ofLightManager::updateAllGreyscale(vector<bool> bDamped){
    for(int i = 0; i < nGreyscale; i++){
        if (bDamped[i]) fadeTo(i, lightLevels[i]);
        else flashTo(i, lightLevels[i]);
    }
}

//----------------------------------------------------
//----------------------------------------------------
/*
template <typename lIndex>
lIndex ofLightManager::lightIndex(int lightNo){
    lIndex pLight;
    if (lightNo < nToggle){
        pLight = bLightsTriggered[lightNo];
    }
    else if (lightNo >= nToggle){
        lightNo = lightNo-nToggle;
        pLight = lightLevels[lightNo];
    }
    return pLight;
}

*/

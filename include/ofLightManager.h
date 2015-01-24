//ofLightManager.h
// object for updating multiple light channels

#pragma once

#include "ofMain.h"
//#include "ofLightSceneManager.h"
#include "ofToggleLight.h"
#include "ofGreyscaleLight.h"

class ofLightManager{
public:
    //constructor
    ofLightManager();
    //destructor
    ~ofLightManager();
    //methods
        // Common methods
        void setup(int _nToggle, int _nGreyscale);

        void draw(int lightType, int lightID);
        bool bReturnState(int lightType, int lightID);

        void drawAll();
        vector<bool> bReturnAllStates();

        // ToggleLights
        void setLightsTriggered(vector<bool> _bLightsTriggered);
//        void setLightsTriggered(ofLightSceneManager &scenes);
        void toggleTrigger(int lightID);
        void setTrigger(int lightID, bool bTriggered);
        bool bReturnTrigger(int lightID);

        void setAllTrigger();

        vector<bool> bReturnAllTrigger();

        // Grayscale Lights
        void setLevels(vector<float> _lightLevels);
        void flashTo(int lightID, float level);
        void fadeTo(int lightID, float level);
        void setDamping(int lightID, float damping);
        void setMaxLevel(int lightID, float level);

        int returnLevel(int lightID);
        float returnDamping(int lightID);
        float returnMaxLevel(int lightID);

        void setAllDamping(float damping);
        void setAllMaxLevel(float level);

        vector<int> returnAllLevels();

        void updateAllGreyscale(vector<bool> bDamped);


        void setupLightIndex();
        template <typename lIndex>
        lIndex lightIndex(int lightNo);

private:
    // objects
    vector<ofToggleLight *> tLights;
    vector<ofGreyscaleLight *> gLights;

    //methods


    //variables
        //common
        int nGreyscale, nToggle, nLights, boxSize, xPos, yPos;

        vector<bool> bLightsTriggered;

        //grayscale
        vector<float> lightLevels;
        vector<int> outputLevels;
};

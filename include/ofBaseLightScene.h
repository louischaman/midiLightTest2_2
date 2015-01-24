// base light scene to derive other scenes from
#pragma once
#include "ofMain.h"

class ofBaseLightScene{
public:
    ofBaseLightScene();
 //   ofBaseLightScene(int nAudioBins, int nToggle, int nGreyscale);

    virtual ~ofBaseLightScene();

    friend class ofLightSceneManager; // MAY CHANGE AS LIGHTSCENES COMES TOGETHER
protected:
    void setup(int nAudioBins, int nToggle, int nGreyscale);
    virtual void scene() = 0;
    void reset();


    int nAudioBins, nToggle, nGreyscale, nLights;
    vector<bool> bTriggered, bDamped;
    vector<float> lightLevels;
private:
};

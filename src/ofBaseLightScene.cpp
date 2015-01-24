#include "ofBaseLightScene.h"

ofBaseLightScene::ofBaseLightScene(){
};

/*ofBaseLightScene::ofBaseLightScene(int _nAudioBins, int _nToggle, int _nGreyscale){
    nAudioBins = _nAudioBins;
    nToggle = _nToggle;
    nGreyscale = _nGreyscale;

    bBeatFlag.assign(nAudioBins, false);
    bTriggered.assign(nToggle, false);
    bDamped.assign(nGreyscale, true);
    lightLevels.assign(nGreyscale, false);
}
*/

ofBaseLightScene::~ofBaseLightScene(){}

void ofBaseLightScene::setup(int _nAudioBins, int _nToggle, int _nGreyscale){
    nAudioBins = _nAudioBins;
    nToggle = _nToggle;
    nGreyscale = _nGreyscale;

  //  bBeatFlag.assign(nAudioBins, false);
    bTriggered.assign(nToggle, false);
    bDamped.assign(nGreyscale, true);
    lightLevels.assign(nGreyscale, 0.0);
}

void ofBaseLightScene::reset(){
    for(int i = 0; i < nToggle; i++){
        bTriggered[i] = false;
    }
    for (int i = 0; i < nGreyscale; i++){
        bDamped[i] = true;
        lightLevels[i] = 0.0;
    }
}

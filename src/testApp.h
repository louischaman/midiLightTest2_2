#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofLightManager.h"
#include <math.h>

/*
channel 16

blaze light 0 is pitch 0x1D
blaze light 1 is pitch 0x0F

normal lights are control 0x08 to 0x0F
*/


class testApp : public ofBaseApp, public ofxMidiListener{

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        //midi
            void midiSetup();
            void newMidiMessage(ofxMidiMessage &eventArgs);

            void midiUpdate();

            ofxMidiIn midiIn;
            ofxMidiMessage midiMessage;
        //lights
            void lightSetup();
            void updateLights();

            ofLightManager lightManager;

            int nTLights;
            int nGLights;

            vector<float> lightLevels;
            vector<bool> bDamped, bToggled;

        //env
            void envSetup();
            float  envAttack, envDecay, envRelease, envSustain , envReleaseD;
            vector<int> envState;

        //arduino stuff
            void arduinoSetup();
            void arduinoUpdate();

            ofSerial serial;
            int baud;
            bool bSendSerialMessage;
            vector<int> arduinoMessage;

        void exit();
};

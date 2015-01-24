#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);

    nTLights = 4;
    nGLights = 8;
    baud = 19200;

    ofSetVerticalSync(true);
    ofBackground(0);
  //  ofSetLogLevel(OF_LOG_VERBOSE);

    lightSetup();

    arduinoSetup();

    midiSetup();
}

void testApp::lightSetup(){
    lightLevels.assign(nGLights, 0.0);
    bDamped.assign(nGLights, false);
    bToggled.assign(nTLights, false);
    lightManager.setup(nTLights, nGLights);
}

void testApp::envSetup(){
        envAttack   =30;
        envDecay    =60;
        envRelease  =10;
        envSustain  =0.6;
        envReleaseD     = pow(0.5,(1/envRelease));
        envState.assign(nGLights, false);

        for(int i = 1 ; i<nGLights;i++){
            lightLevels[i]=0;
            envState[i]=4;
        }
}

void testApp::arduinoSetup(){
    int i = 0;
    arduinoMessage.assign(16, ' ');
    i++;
    arduinoMessage[i] = 0;
    i++;
    for(int j = 0; j < nTLights; j++){
            arduinoMessage[i] = 0;
            i++;
    }

    arduinoMessage[i] = 'g';
    for(int j = 0; j < nGLights; j++){
            arduinoMessage[i] = 0;
            i++;
    }

    arduinoMessage[i] = 'e';
    //cout << "Serial Message Size: " << arduinoMessage.size() << endl;
    bSendSerialMessage = false;

    unsigned char aMsg[arduinoMessage.size()];
    for (int j = 0; j < arduinoMessage.size(); j++){
        aMsg[j] = arduinoMessage[j];
    }
    //cout << "message ready" << endl;
    serial.setup("COM3", baud);
    //cout << "serial ready" << endl;
    for (int j = 0; j < 16; j++){
        serial.writeByte(aMsg[j]);
        //cout << j << endl;
    }

    //cout << "serial written" << endl;
}

void testApp::midiSetup(){
    midiIn.listPorts();
    midiIn.openPort(1);
    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    midiIn.setVerbose(true);
}

//--------------------------------------------------------------
void testApp::update(){
    midiUpdate();

    updateLights();

    //arduinoUpdate();
}

void testApp::arduinoUpdate(){
    if(serial.isInitialized()){
        int i = 2;
        for(int j = 0; j < nTLights; j++){
            arduinoMessage[i] = static_cast<int>(bToggled[j]);
            i++;
        }
        i++;
        for (int j =0; j < nGLights; j++){
            arduinoMessage[i] = lightManager.returnLevel(j);
            i++;
            if(i > arduinoMessage.size()) break;
        }
        unsigned char aMsg[arduinoMessage.size()];
        for(int j = 0; j < arduinoMessage.size(); j++){
            aMsg[j] = arduinoMessage[j];
        }
        serial.writeBytes(aMsg, arduinoMessage.size());
    }



}


void testApp::midiUpdate(){
    if(midiMessage.status==0x90){
        if(midiMessage.pitch==29) bToggled[0] = true;
        else if(midiMessage.pitch==15) bToggled[1] = true;
        else if(midiMessage.pitch==0x11) bToggled[2] = true;
        else if(midiMessage.pitch==0x1B) bToggled[3] = true;
    }else if(midiMessage.status==0x80){
        if(midiMessage.pitch==29) bToggled[0] = false;
        else if(midiMessage.pitch==15) bToggled[1] = false;
        else if(midiMessage.pitch==0x11) bToggled[2] = false;
        else if(midiMessage.pitch==0x1B) bToggled[3] = false;
    }else if(midiMessage.status==0xB0){
        int control = midiMessage.control;
        if((control >= 0x08) && (control <= 0x0F)){
            control -= 8;
  //          lightLevels[control] = ofMap(static_cast<float>(midiMessage.value), 0.0, 127.0, 0.0, 1.0);
        }
    }
}

void testApp::updateLights(){





    lightManager.setLightsTriggered(bToggled);
    lightManager.setAllTrigger();
    lightManager.setLevels(lightLevels);
    lightManager.updateAllGreyscale(bDamped);
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(200);
    ofDrawBitmapString(ofToString(midiMessage.pitch), 20, 20);
    lightManager.drawAll();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

void testApp::exit(){
    midiIn.closePort();
    midiIn.removeListener(this);
}

void testApp::newMidiMessage(ofxMidiMessage &msg){
    midiMessage = msg;
}

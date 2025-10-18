//
//  LEDs.hpp
//  waveVagrants
//

#ifndef LEDs_hpp
#define LEDs_hpp

#include <stdio.h>
#include "ofMain.h"
#include "LED.hpp"
#include "ofxOsc.h"
#include "ofxNetwork.h"

#define NUM_TEENSY_LEDs 81
#define NUM_TOTAL_LEDs 162
#define UDP_BUFFER_SIZE 245

class LEDs {
public:
    LEDs();
    
    void update();
    void draw();
    void sendUdp();
    
    void setSystemSize(float width, float height);
    void setSize(float width, float height);
    void setOceanFbo(ofFbo& oceanFbo);
    void analyzeSubscreen();
    void packTeensyUdp(int whichTeensy, u_int8_t data[]);
    
    float systemWidth, systemHeight;
    float width, height;
    float LEDSpacing;
    
    vector <LED> leds;
    
    u_int8_t data1[UDP_BUFFER_SIZE];
    u_int8_t data2[UDP_BUFFER_SIZE];
    u_int8_t data3[UDP_BUFFER_SIZE];
    
    ofxUDPManager udpConnection1;
    ofxUDPManager udpConnection2;
    ofxUDPManager udpConnection3;
};

#endif /* LEDs_hpp */

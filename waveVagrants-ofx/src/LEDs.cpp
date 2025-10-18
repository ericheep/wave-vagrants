//
//  LEDs.cpp
//  waveVagrants
//

#include "LEDs.hpp"

LEDs::LEDs() {
    for (int i = 0; i < NUM_TOTAL_LEDs; i++) {
        LED led;
        leds.push_back(led);
    }
    
    udpConnection1.Create();
    udpConnection1.Connect("10.52.120.10", 8888);
    udpConnection1.SetNonBlocking(true);

    udpConnection2.Create();
    udpConnection2.Connect("10.52.120.11", 8888);
    udpConnection2.SetNonBlocking(true);
    
    //udpConnection3.Create();
    //udpConnection3.Connect("10.52.120.12", 8888);
    //udpConnection3.SetNonBlocking(true);
    
    // set check bytes
    data1[0] = 127;
    data1[1] = 127;
    data2[0] = 127;
    data2[1] = 127;
    data3[0] = 127;
    data3[1] = 127;
}

void LEDs::update() {
    for (int i = 0; i < NUM_TOTAL_LEDs; i++) {
        leds[i].update();
    }
    
    sendUdp();
}

void LEDs::draw() {
    for (int i = 0; i < NUM_TOTAL_LEDs; i++) {
        leds[i].draw();
    }
}

void LEDs::setSystemSize(float _width, float _height) {
    systemWidth = _width;
    systemHeight = _height;
}

void LEDs::setSize(float _width, float _height) {
    width = _width;
    height = _height;
    
    LEDSpacing = width / NUM_TOTAL_LEDs;

    ofVec2f center = ofVec2f(systemWidth / 2.0, systemHeight / 2.0);
    ofVec2f startingPoint = ofVec2f(center.x - width / 2.0, center.y + 100);
    
    for (int i = 0; i < NUM_TOTAL_LEDs; i++) {
        // from center
        float x = startingPoint.x + width / NUM_TOTAL_LEDs * i + LEDSpacing;
        float y = startingPoint.y;

        leds[i].set(x, y, LEDSpacing, LEDSpacing);
        leds[i].setSubsection(x, y - 100, LEDSpacing, 100);
    }
}

void LEDs::setOceanFbo(ofFbo& oceanFbo) {
    for (int i = 0; i < NUM_TOTAL_LEDs; i++) {
        leds[i].setOceanFbo(oceanFbo);
    }
}

void LEDs::packTeensyUdp(int whichTeensy, u_int8_t data[]) {
    // offset for which Teensy we're sending to
    int ledTeensyOffset = NUM_TEENSY_LEDs * whichTeensy;
    
    // offset for check bytes
    int led = 2;
    
    for (int i = 0; i < NUM_TEENSY_LEDs; i++) {
        ofColor c = leds[i + ledTeensyOffset].ledColor;
        
        data[led] = c.r;
        led++;
        data[led] = c.g;
        led++;
        data[led] = c.b;
        led++;
    }
}

void LEDs::sendUdp() {
    packTeensyUdp(0, data1);
    packTeensyUdp(1, data2);
    // packGhostUdp(2, data3);

    udpConnection1.Send((const char*)data1, sizeof(data1));
    udpConnection2.Send((const char*)data2, sizeof(data2));
    //udpConnection3.Send((const char*)data3, sizeof(data3));
}
